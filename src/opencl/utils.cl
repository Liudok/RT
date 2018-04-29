#include "include/kernel.h"

constant int numX = 512, numY = 512, num_octaves = 7;
constant float persistence = 0.5;

constant int primes[][3] = {
	{ 995615039, 600173719, 701464987 },
	{ 831731269, 162318869, 136250887 },
	{ 174329291, 946737083, 245679977 },
	{ 362489573, 795918041, 350777237 },
	{ 457025711, 880830799, 909678923 },
	{ 787070341, 177340217, 593320781 },
	{ 405493717, 291031019, 391950901 },
	{ 458904767, 676625681, 424452397 },
	{ 531736441, 939683957, 810651871 },
	{ 997169939, 842027887, 423882827 }
};

constant uint max_prime_index = sizeof(primes) / sizeof(int) - 1;

static float noise(int i, int x, int y)
{
	int n = x + y * 57;
	n = (n << 13) ^ n;
	int a = primes[i][0], b = primes[i][1], c = primes[i][2];
	int t = (n * (n * n * a + b) + c) & 0x7fffffff;
	return 1.0 - native_divide(t, 1073741824.0f);
}

static float smoothed_noise(int i, int x, int y)
{
	float corners = (noise(i, x - 1, y - 1) + noise(i, x + 1, y - 1) +
			noise(i, x - 1, y + 1) + noise(i, x + 1, y + 1)) / 16;
	float sides = native_divide(noise(i, x - 1, y) + noise(i, x + 1, y) +
			noise(i, x, y - 1) + noise(i, x, y + 1), 8);
	float center = noise(i, x, y) / 4;
	return corners + sides + center;
}

static float interpolate(float a, float b, float x)
{ // cosine interpolation
	float ft = x * M_PI;
	float f = (1 - native_cos(ft)) * 0.5;
	return a * (1 - f) + b * f;
}

static float interpolated_noise(int i, float x, float y)
{
	int integer_X = x;
	float fractional_X = x - integer_X;
	int integer_Y = y;
	float fractional_Y = y - integer_Y;

	float v1 = smoothed_noise(i, integer_X, integer_Y),
		   v2 = smoothed_noise(i, integer_X + 1, integer_Y),
		   v3 = smoothed_noise(i, integer_X, integer_Y + 1),
		   v4 = smoothed_noise(i, integer_X + 1, integer_Y + 1),
		   i1 = interpolate(v1, v2, fractional_X),
		   i2 = interpolate(v3, v4, fractional_X);
	return interpolate(i1, i2, fractional_Y);
}

static float perlin_noise(float2 uv)
{
	float total = 0;
	float frequency = native_powr(2.f, num_octaves);
	float amplitude = 1;

	for (int i = 0; i < num_octaves; ++i) {
		frequency /= 2;
		amplitude *= persistence;
		total += interpolated_noise(i % max_prime_index,
				uv.x / frequency, uv.y / frequency)
			* amplitude;
	}
	return total / frequency;
}

static float get_random(unsigned int* seed0, unsigned int* seed1)
{
	/* hash the seeds using bitwise AND operations and bitshifts */
	*seed0 = 36969 * ((*seed0) & 65535) + ((*seed0) >> 16);
	*seed1 = 18000 * ((*seed1) & 65535) + ((*seed1) >> 16);

	unsigned int ires = ((*seed0) << 16) + (*seed1);

	/* use union struct to convert int to float */
	union {
		float f;
		unsigned int ui;
	} res;

	res.ui = (ires & 0x007fffff) | 0x40000000; /* bitwise AND, bitwise OR */
	return native_divide((res.f - 2.0f), 2.0f);
}

static void ft_roots(float2* t, float a, float b, float c)
{
	float deskr;

	deskr = b * b - 4 * a * c;
	if (deskr >= 0.f && a != 0.f)
		*t = (float2)(native_divide(-b + native_sqrt(deskr), 2 * a),
				native_divide(-b - native_sqrt(deskr), 2 * a));
	else
		*t = (float2)(INFINITY, INFINITY);
}

static int to_int(float3 v)
{
	float3 t;
	union {
		uchar4 byte;
		uint value;
	} color;

	t = native_powr(clamp(v, 0.f, 1.0f), native_recip(2.2f));
	color.byte[0] = (int)(t.z * 255.0f + .5f);
	color.byte[1] = (int)(t.y * 255.0f + .5f);
	color.byte[2] = (int)(t.x * 255.0f + .5f);
	color.byte[3] = 0x0;
	return (color.value);
}

static void add_sample(global float3* colors,
		float3* color,
		uint currentSample,
		int id)
{
	if (currentSample == 0) {
		colors[id] = *color;
	} else {
		const float k1 = currentSample;
		const float k2 = native_recip(currentSample + 1.f);
		colors[id].x = (colors[id].x * k1 + color->x) * k2;
		colors[id].y = (colors[id].y * k1 + color->y) * k2;
		colors[id].z = (colors[id].z * k1 + color->z) * k2;
	}
}

static void put_pixel(global int* pixels, global float3* colors, int id)
{
	pixels[id] = to_int(colors[id]);
}

static float2 sphere_tex_coords(t_surface* surf)
{
	return (float2)(
			native_divide(atan2pi(surf->nl.z, surf->nl.x), 2.f) + 0.5f,
			0.5f - asinpi(surf->nl.y));
}

static float2 cylinder_tex_coords(t_surface* surf)
{
	// ETO ZAGLUSHKA NEED HELP
	float3 nl = fract(surf->pos - surf->obj->prim.cylinder.origin, (float3*)NULL);
	return (float2)(
			native_divide(atan2pi(nl.z, nl.x), 2.f) + 0.5f,
			0.5f - asinpi(nl.y));
}

static float2 planar_tex_coords(t_surface* surf, float3 pos)
{
	float3 u = cross(surf->nl, (float3)(0.f, 1.f, 0.f));
	if (fast_length(u) == 0.f)
		u = cross(surf->nl, (float3)(0.f, 0.f, 1.f));
	float3 v = cross(surf->nl, u);
	float3 vec = surf->pos - pos;
	return fract((float2)(dot(u, vec), dot(v, vec)), (float2*)NULL);
}

static float2 get_tex_coords(t_surface* surf)
{
	switch (surf->obj->type) {
		case sphere:
		case torus:
			return (sphere_tex_coords(surf));
		case plane:
			return (planar_tex_coords(surf, surf->obj->prim.plane.origin));
		case disk:
			return (planar_tex_coords(surf, surf->obj->prim.disk.origin));
		case cylinder:
			return (cylinder_tex_coords(surf));
		default:
			break;
	}
	return ((float2)(0, 0));
}

constant sampler_t sampler_tex = CLK_FILTER_NEAREST | CLK_NORMALIZED_COORDS_FALSE;

static float3 get_texel(read_only image2d_array_t textures,
		t_surface* surf, int tex_num, uint2 size)
{
	float2 uv = surf->uv * convert_float2(size);
	float2 fl;
	float2 fraction = fract(uv, &fl);
	int2 t[] = {
		{fl.x, fl.y},
		{fl.x + 1, fl.y},
		{fl.x + 1, fl.y + 1},
		{fl.x, fl.y + 1}
	};
	float3 pixels[4];
	for (int i = 0; i < 4; ++i)
		pixels[i] = read_imagef(textures, sampler_tex, (int4)(t[i], tex_num, 0)).zyx;
	float3 result = mix(mix(pixels[0], pixels[1], fraction.x), mix(pixels[3], pixels[2], fraction.x), fraction.y);
	return result;
//	return (read_imagef(textures, sampler_tex, (int4)(convert_int2(uv), tex_num, 0)).zyx);
}
