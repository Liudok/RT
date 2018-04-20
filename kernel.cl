
#define KERNEL_ONLY
#include "include/kernel.h"

static constant t_object	objs[] = {
	{{1,0,0,0}, {.75, .25, .25}, sphere, {.sphere = {{1e5 + 1, 40.8, 81.6}, 1e5}}},
	{{1,0,0,0}, {.25, .25, .75}, sphere, {.sphere = {{-1e5 + 99, 40.8, 81.6}, 1e5}}},
	{{1,0,0,0}, {.75, .75, .75}, sphere, {.sphere = {{50, 40.8, 1e5}, 1e5}}},
	// {{1,0,0,0}, {0, 0, 0}, sphere, {.sphere = {{50, 40.8, -1e5 + 170}, 1e5}}},
	{{1,0,0,0}, {.75, .75, .75}, sphere, {.sphere = {{50, 1e5, 81.6}, 1e5}}},
	{{1,0,0,0}, {.75, .75, .75}, sphere, {.sphere = {{50, -1e5 + 81.6, 81.6}, 1e5}}},
	{{1,0,0,0}, {.85, .85, .85}, sphere, {.sphere = {{27, 16.5, 47}, 16.5}}},
	{{1,0,0,0}, {.85, .85, .85}, sphere, {.sphere = {{73, 16.5, 78}, 16.5}}},
	{{0,0,0,1}, {12, 12, 12}, sphere, {.sphere = {{50, 681.6 - .27, 81.6}, 600}}},
};

// static constant t_object	objs[] = {
// 	// {{1,0,0,0}, {.25, .25, .75}, sphere, {.sphere = {{0,0,0}, 30}}},
// 	{{1,0,0,0}, {.45, .75, .45}, sphere, {.sphere = {{2,-1,20}, 1}}},
// 	{{1,0,0,0}, {.75, .45, .45}, sphere, {.sphere = {{-1,0,20}, 1}}},
// 	{{0,0,0,1}, {1, 1, 1}, sphere, {.sphere = {{0, 4, 19}, 1}}},
// };

static constant int			objnum = sizeof(objs) / sizeof(t_object);

static constant t_camera 	camera = {
	{50, 52, 295.6}, {0, -0.049938, -0.998752},
	{0.684667, 0, 0}, {0, 0.512859, -0.025643},
	{1024, 768}
};

// static constant t_camera 	camera = {
// 	{0, 0, 0}, {0, 0, 1},
// 	{0.684667, 0, 0}, {0, 0.512859, -0.025643},
// 	{1024, 768}
// };


static float get_random(unsigned int *seed0, unsigned int *seed1) {

	/* hash the seeds using bitwise AND operations and bitshifts */
	*seed0 = 36969 * ((*seed0) & 65535) + ((*seed0) >> 16);
	*seed1 = 18000 * ((*seed1) & 65535) + ((*seed1) >> 16);

	unsigned int ires = ((*seed0) << 16) + (*seed1);

	/* use union struct to convert int to float */
	union {
		float f;
		unsigned int ui;
	} res;

	res.ui = (ires & 0x007fffff) | 0x40000000;  /* bitwise AND, bitwise OR */
	return half_divide((res.f - 2.0f), 2.0f);
}

static void ft_roots(float2 *t, float a, float b, float c)
{
	float	deskr;

	deskr = b * b - 4 * a * c;
	if (deskr >= 0.f && a != 0.f)
		*t = (float2)(	native_divide(-b + native_sqrt(deskr), 2 * a),
						native_divide(-b - native_sqrt(deskr), 2 * a));
	else
		*t = (float2)(-1, -1);
}

static float  sphere_intersect(constant t_sphere *obj,
								float3 ray_dir,
								float3 ray_origin)
{
	// float	a;
	// float	b;
	// float	c;
	// float3	oc;
	// float2	t;

	// oc = ray_origin - obj->origin;
	// a = dot(ray_dir, ray_dir);
	// b = 2 * dot(ray_dir, oc);
	// c = dot(oc, oc) - (obj->radius * obj->radius);
	// ft_roots(&t, a, b, c);
	// if ((t.x < 0.0 && t.y >= 0.0) || (t.y < 0.0 && t.x >= 0.0))
	// 	return t.x > t.y ? t.x : t.y;
	// else
	// 	return t.x < t.y ? t.x : t.y;
	float3	oc;
	float	b;
	float	dis;
	float	t;

	oc = obj->origin - ray_origin;
	b = dot(oc, ray_dir);
	dis = b * b - dot(oc, oc) + obj->radius * obj->radius;
	if (dis < 0)
		return 0;
	dis = sqrt(dis);
	return ((t = b - dis) > 1e-4) ? t : ((t = b + dis) > 1e-4) ? t : 0;
}

static float3	sphere_normal(constant t_sphere *obj, float3 pos)
{
	return (normalize(pos - obj->origin));
}

static float  plane_intersect(constant t_plane *obj,
								float3 ray_dir,
								float3 ray_origin)
{
	float	denom;
	float3	oc;

	if ((denom = dot(ray_dir, obj->normal)) == 0)
		return (-1);
	oc = ray_origin - obj->origin;
	return (-dot(oc, obj->normal) / denom);
}

static float3	plane_normal(constant t_plane *obj)
{
	return (normalize(obj->normal));
}

static float  cylinder_intersect(constant t_cylinder *obj,
								float3 ray_dir,
								float3 ray_origin,
								float *m)
{
	float	a;
	float	b;
	float	c;
	float3	oc;
	float2	t;

	oc = ray_origin - obj->origin;
	t.x = dot(ray_dir, normalize(obj->normal));
	t.y = dot(oc, normalize(obj->normal));
	a = dot(ray_dir, ray_dir) - t.x * t.x;
	b = 2 * (dot(ray_dir, oc) - t.x * t.y);
	c = dot(oc, oc) - t.y * t.y - obj->r2;
	ft_roots(&t, a, b, c);
	if ((t.x  < 0.0f) && (t.y < 0.0f))
		return (-1);
	if ((t.x  < 0.0f) || (t.y < 0.0f))
	{
		a = (t.x > t.y) ? t.x : t.y;
		*m  = dot(ray_dir, normalize(obj->normal)) * a + dot(oc, fast_normalize(obj->normal));
		return ((*m <= obj->height) && (*m >= 0) ? t.x : -1);
	}
	a = (t.x < t.y) ? t.x : t.y;
	*m  = dot(ray_dir, normalize(obj->normal)) * a + dot(oc, fast_normalize(obj->normal));
	if ((*m <= obj->height) && (*m >= 0))
		return (a);
	a = (t.x >= t.y) ? t.x : t.y;
	*m  = dot(ray_dir, normalize(obj->normal)) * a + dot(oc, fast_normalize(obj->normal));
	if ((*m <= obj->height) && (*m >= 0))
		return (a);
	return (-1);
}

static float3	cylinder_normal(constant t_cylinder *obj, float3 pos, float m)
{
	return (normalize(pos - obj->origin - fast_normalize(obj->normal) * m));
}

static float  cone_intersect(constant t_cone *obj,
								float3 ray_dir,
								float3 ray_origin,
								float *m)
{
	float	a;
	float	b;
	float	c;
	float 	d;
	float3	oc;
	float2	t;

	oc = ray_origin - obj->origin;
	t.x = dot(ray_dir, normalize(obj->normal));
	t.y = dot(oc, normalize(obj->normal));
	d = 1 + obj->half_tangent * obj->half_tangent;
	a = dot(ray_dir, ray_dir) - d * t.x * t.x;
	b = 2 * (dot(ray_dir, oc) - d * t.x * t.y);
	c = dot(oc, oc) - d * t.y * t.y;
	ft_roots(&t, a, b, c);
	if ((t.x  < 0.0f) && (t.y < 0.0f))
		return (-1);
	if ((t.x  < 0.0f) || (t.y < 0.0f))
	{
		a = (t.x > t.y) ? t.x : t.y;
		*m  = dot(ray_dir, normalize(obj->normal)) * a + dot(oc, fast_normalize(obj->normal));
		return ((*m <= obj->m2) && (*m >= obj->m1) ? t.x : -1);
	}
	a = (t.x < t.y) ? t.x : t.y;
	*m  = dot(ray_dir, normalize(obj->normal)) * a + dot(oc, fast_normalize(obj->normal));
	if ((*m <= obj->m2) && (*m >= obj->m1))
		return (a);
	a = (t.x >= t.y) ? t.x : t.y;
	*m  = dot(ray_dir, normalize(obj->normal)) * a + dot(oc, fast_normalize(obj->normal));
	if ((*m <= obj->m2) && (*m >= obj->m1))
		return (a);
	return (-1);
}

static float3	cone_normal(constant t_cone *obj, float3 pos, float m)
{
	return (normalize(pos - obj->origin - normalize(obj->normal) * m * (1 + obj->half_tangent * obj->half_tangent)));
}

static float  disk_intersect(constant t_disk *obj,
								float3 ray_dir,
								float3 ray_origin)
{
	float	denom;
	float3	oc;
	float	t;
	float3 	pos;

	if ((denom = dot(ray_dir, obj->normal)) == 0)
		return (-1);
	oc = ray_origin - obj->origin;
	t = -dot(oc, obj->normal) / denom;
	if (t < 0)
		return (-1.0f);
	pos = ray_origin + t * ray_dir;
	pos -= obj->origin;
	if (dot(pos, pos) <= obj->radius2)
		return (t);
	return (-1);
}

static float3	disk_normal(constant t_disk *obj)
{
	return (normalize(obj->normal));
}

static void		intersect(	constant t_object *obj,
							t_ray ray,
							constant t_object **closest,
							float	*closest_dist,
							float 	*m)
{
	float current;
	switch (obj->type) {
		case sphere:
			current = sphere_intersect(&obj->prim.sphere, ray.d, ray.o);
			break;
		case plane:
			current = plane_intersect(&obj->prim.plane, ray.d, ray.o);
			break;
		case cylinder:
			current = cylinder_intersect(&obj->prim.cylinder, ray.d, ray.o, m);
			break;
		case cone:
			current = cone_intersect(&obj->prim.cone, ray.d, ray.o, m);
			break;
		case disk:
			current = disk_intersect(&obj->prim.disk, ray.d, ray.o);
			break;
		default:
			break;
	}
	if (current <= 0.0 || current > *closest_dist)
		return ;
	*closest_dist = current;
	*closest = obj;
}

static float3	find_normal(constant t_object *obj, float3 hit_pos, float m)
{
	switch (obj->type) {
		case sphere:
			return (sphere_normal(&obj->prim.sphere, hit_pos));
		case plane:
			return (plane_normal(&obj->prim.plane));
		case cylinder:
			return (cylinder_normal(&obj->prim.cylinder, hit_pos, m));
		case cone:
			return (cone_normal(&obj->prim.cone, hit_pos, m));
		case disk:
			return (disk_normal(&obj->prim.disk));
		default:
			break;
	}
	return ((float3)(0,0,0));
}

static int	toInt(float3 v)
{
	float3 		t;
	union
	{
		uchar4	byte;
		uint	value;
	}			color;

	t = pow(clamp(v, 0.f, 1.0f), 1.f / 2.2f);
	color.byte[0] = (int)(t.z * 255 + .5);
	color.byte[1] = (int)(t.y * 255 + .5);
	color.byte[2] = (int)(t.x * 255 + .5);
	color.byte[3] = 0x0;
	return (color.value);
}

static t_surface   get_surface_properties(constant t_object	*obj, t_ray r, float t)
{
    t_surface   s;

    s.obj = obj;
    s.pos = r.o + r.d * t;
    s.n = find_normal(obj, s.pos, 0 /*<-- m?*/);
    s.nl = dot(s.n, r.d) < 0 ? s.n : s.n * -1;
    s.material = (obj->material.w) ? emission : diffuse;
    s.f = (s.material != emission) ? s.obj->color : (float3){0,0,0};
    s.maxref = (s.material != emission) ? fmax(fmax(s.f.x, s.f.y), s.f.z) : 0;
    
    return (s);
}

static t_ray   diffuse_reflection(t_surface surf, uint *seeds)
{
    float  r1, r2, r2s;
    float  cos_a, sin_a, k;
    float3   w, u, v, d;
    t_ray	rand_ray;

    r1 = 2 * M_PI * get_random(&seeds[0], &seeds[1]);
    r2 = get_random(&seeds[0], &seeds[1]);
    r2s = sqrt(r2);
    w = surf.nl;
    u = normalize(cross((fabs(w[0]) > .1 ? (float3){0, 1, 0} : (float3){1, 0, 0}), w));
    v = cross(w, u);
    cos_a = cos(r1);
    sin_a = sin(r1);
    k = sqrt(1 - r2);
    u = u * cos_a * r2s;
    v = v * sin_a * r2s;
    w = w * k;
    d = normalize(u + v + w);
    rand_ray.o = surf.pos;
    rand_ray.d = d;
    return (rand_ray);
}

static float3   radiance(float3 ray_dir, float3 ray_orig, uint *seeds)
{
    int         		depth = 0; // bounces counter
    constant t_object	*obj;
    float 	    		t; // distance to hit
    float3      		cl = {0, 0, 0}; // accumulated color
    float3      		cf = {1, 1, 1}; // accumulated reflectance
    t_surface   		surf; // surface propertiess
    t_ray				r;

    r.d = ray_dir;
    r.o = ray_orig;
    while (1)
    {
		obj = NULL;
		t = MAXFLOAT;

		for (int i = 0; i < objnum; i++)
			intersect(&objs[i], r, &obj, &t, 0);
		if (obj && t < MAXFLOAT)
		{
			surf = get_surface_properties(obj, r, t);
	        cl += (surf.material == emission) ? cf * obj->color : 0;
	        if (++depth > 5)
	        {
	            if (get_random(&seeds[0], &seeds[1]) < surf.maxref)
	                surf.f /= surf.maxref;
	            else
	                return (clamp(cl, 0.f, 1.0f));
	        }
	        cf = cf * surf.f;
	        if (surf.material == diffuse || surf.material == emission)
	            r = diffuse_reflection(surf, seeds);
	        // return cf;
		}
		else
			return (clamp(cl, 0.f, 1.0f));
    }
}



__kernel __attribute__((vec_type_hint ( float3 )))
void	path_tracing(	/*t_scene scene,*/
						global uint *inputSeeds,
						global float3 *colors,
						global int *pixels,
						uint samples)
{
	int		i = get_global_id(0);
	uint2	coords = {i % camera.canvas.x, i / camera.canvas.x};
	uint	seeds[2];
	float3	rad = {0, 0, 0};
	float3	dir;

	seeds[0] = inputSeeds[i * 2];
	seeds[1] = inputSeeds[i * 2 + 1];
	// Each pixel divide by 4 sub-pixels
	for (size_t sy = 0; sy < 2; sy++)
	{
		for (size_t sx = 0; sx < 2; sx++)
		{
				// Init ray dir on 'table tent' term
				float r1 = 2 * get_random(&seeds[0], &seeds[1]);
				float r2 = 2 * get_random(&seeds[0], &seeds[1]);
				float dx = (r1 < 1) ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
				float dy = (r2 < 1) ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);
				dx = ((sx + 0.5 + dx) / 2.0 + coords.x) / (float)camera.canvas.x - 0.5;
				dy = ((sy + 0.5 + dy) / 2.0 + coords.y) / (float)camera.canvas.y - 0.5;
				dir = normalize(camera.cx * dx + camera.cy * dy + camera.dir);

				// Compute sub-pixel radiance and save divide by 4
				rad += radiance(dir, camera.origin + dir, seeds) * 0.25f;
		}
	}
	if (samples == 0) {
		colors[i] = rad;
	} else {
		const float k1 = samples;
		const float k2 = 1.f / (samples + 1.f);
		colors[i].x = (colors[i].x * k1  + rad.x) * k2;
		colors[i].y = (colors[i].y * k1  + rad.y) * k2;
		colors[i].z = (colors[i].z * k1  + rad.z) * k2;
	}

	PUT_PIXEL(
		pixels,
		camera.canvas.x,
		coords.x,
		(camera.canvas.y - coords.y - 1),
		colors[i]
	);
	inputSeeds[i * 2] = seeds[0];
	inputSeeds[i * 2 + 1] = seeds[1];
}