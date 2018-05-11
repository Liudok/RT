#include "include/kernel.h"

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
	int a = primes[i][0];
   	int b = primes[i][1];
	int c = primes[i][2];
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
	float frequency = native_powr(2.f, 7);
	float amplitude = 1;

	for (int i = 0; i < 7; ++i) {
		frequency /= 2;
		amplitude /= 2;
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
	union {
		uchar4 byte;
		uint value;
	} color;

	v = native_powr(v, native_recip(2.2f));
	color.byte[0] = (int)(v.z * 255.0f + .5f);
	color.byte[1] = (int)(v.y * 255.0f + .5f);
	color.byte[2] = (int)(v.x * 255.0f + .5f);
	color.byte[3] = 0x0;
	return (color.value);
}

static void add_sample(global float3* colors,
		float3 color,
		uint currentSample,
		int id)
{
	if (currentSample == 0) {
		colors[id] = color;
	} else {
		const float k1 = currentSample;
		const float k2 = native_recip(currentSample + 1.f);
		colors[id] = (colors[id] * k1 + color) * k2;
	}
}

static void put_pixel(global int* pixels, float3 color, int id)
{
	pixels[id] = to_int(color);
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

static float2 cone_tex_coords(t_surface* surf, float3 pos)
{
	global t_cone *cone = &surf->obj->prim.cone;
	float3 u = cone->normal;
	float3 vec = surf->pos - pos;
	float t;
	float s = fract(dot(u, vec), &t);
	t /= max(cone->m1, cone->m2);
	return ((float2)(t,s));
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
		case cone:
			return (cone_tex_coords(surf, surf->obj->prim.cone.origin));
		case disk:
			return (planar_tex_coords(surf, surf->obj->prim.disk.origin));
		case cylinder:
			return (cylinder_tex_coords(surf));
		default:
			break;
	}
	return ((float2)(0, 0));
}

static float3 get_texel(read_only image2d_array_t textures,
		t_surface* surf, int tex_num, uint2 size)
{
	float2 uv = surf->uv * convert_float2(size - (uint2)(1,1));
	float2 fl;
	float2 fraction = fract(uv, &fl);
	const int2 t[] = {
		{fl.x, fl.y},
		{fl.x + 1, fl.y},
		{fl.x, fl.y + 1},
		{fl.x + 1, fl.y + 1}
	};
	float3 pixels[4];
	for (int i = 0; i < 4; ++i)
		pixels[i] = read_imagef(textures,
						(int4)(t[i], tex_num, 0)).zyx;
	float3 result =
		mix(
			mix(pixels[0], pixels[1], fraction.x),
			mix(pixels[2], pixels[3], fraction.x),
		fraction.y);
	return result;
}

static float3 get_color(global float3 *colors, int2 canvas, int2 coords)
{
	if (coords.x >= canvas.x)
		coords.x = canvas.x - 1;
	else if (coords.y >= canvas.y)
		coords.y = canvas.y - 1;
	if (coords.x < 0)
		coords.x = 0;
	else if (coords.y < 0)
		coords.y = 0;
	return (colors[coords.x + coords.y * canvas.x]);
}

static float3 black_white(float3 col)
{
	float average = (col.x + col.y + col.z) / 3;
	col = (float3)(average);
	return (col);
}

constant float matrix[][7] = {
	{ 0.00134f, 0.00408f, 0.00794f, 0.00992f, 0.00794f, 0.00408f, 0.00134f },
	{ 0.00408f, 0.01238f, 0.02412f, 0.03012f, 0.02412f, 0.01238f, 0.00408f },
	{ 0.00794f, 0.02412f, 0.04698f, 0.05867f, 0.04698f, 0.02412f, 0.00794f },
	{ 0.00992f, 0.03012f, 0.05867f, 0.07327f, 0.05867f, 0.03012f, 0.00992f },
	{ 0.00794f, 0.02412f, 0.04698f, 0.05867f, 0.04698f, 0.02412f, 0.00794f },
	{ 0.00408f, 0.01238f, 0.02412f, 0.03012f, 0.02412f, 0.01238f, 0.00408f },
	{ 0.00134f, 0.00408f, 0.00794f, 0.00992f, 0.00794f, 0.00408f, 0.00134f }
};

static float3 blur(global float3 *colors, int2 canvas, int2 coords)
{
	float3 current = 0;

	for (int i = -3; i < 4; i++)
		for (int j = -3; j < 4; j++)
			current += get_color(colors, canvas, coords + (int2)(i,j)) * matrix[i + 3][j + 3];
	return (current);
}

static float3 edge_detection(global float3 *colors, int2 canvas, int2 coords)
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
		{
			float3 a = get_color(colors, canvas, coords + (int2)(i,j));
			float3 b = get_color(colors, canvas, coords - (int2)(i,j));
			if (fast_distance(a, b) > 0.1f || fabs(a.x - b.x) > 0.05 ||
					fabs(a.y - b.y) > 0.05|| fabs(a.z - b.z) > 0.05)
				return (float3)(1,1,1);
		}
	return (float3)(100,100,100);
}

static float3 cartoon(global float3 *colors, int2 canvas, int2 coords)
{
	float3 result = blur(colors, canvas, coords) *
		edge_detection(colors, canvas, coords);
	uchar3 cartoon = { result.x, result.y, result.z };
	result = (float3)(cartoon.x, cartoon.y, cartoon.z);
	result /= 5.f;
	return(result);
}

static float3 negative(float3 col)
{
	return ((float3)(1,1,1) - cbrt(col));
}

static float3   sepia(float3 col)
{
	float3 res = {
		clamp(col.x * .6f + col.y * .8f + col.z * .6f, 0.0005f, 1.f),
		clamp(col.x * .349f + col.y * .686f + col.z * .168f, 0.0004f, 1.f),
		clamp(col.x * .272f + col.y * .534f + col.z * .131f, 0.f, 1.f)
	};
	return (res);
}
