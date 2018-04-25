
#include "include/kernel.h"

static float3	sphere_normal(global t_sphere *obj, float3 pos)
{
	return (normalize(pos - obj->origin));
}

static float3	plane_normal(global t_plane *obj)
{
	return (normalize(obj->normal));
}

static float3	cylinder_normal(global t_cylinder *obj, float3 pos, float m)
{
	return (normalize(pos - obj->origin - fast_normalize(obj->normal) * m));
}

static float3	cone_normal(global t_cone *obj, float3 pos, float m)
{
	return (normalize(pos - obj->origin - normalize(obj->normal) * m * (1 + obj->half_tangent * obj->half_tangent)));
}

static float3	disk_normal(global t_disk *obj)
{
	return (normalize(obj->normal));
}

static float3	torus_normal(global t_torus *obj, float3 pos)
{
	float 	k;
	float3	a;
	float 	m;

	k = dot(pos - obj->origin, obj->normal);
	a = pos - obj->normal * k;
	m = sqrt(obj->small_radius2 - k * k);
	return (normalize(pos - a - (obj->origin - a) * m / (sqrt(obj->big_radius2) + m)));
}

static float3	find_normal(global t_object *obj, float3 hit_pos, float m)
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
		case torus:
			return (torus_normal(&obj->prim.torus, hit_pos));
		default:
			break;
	}
	return ((float3)(0,0,0));
}

static t_material  get_material(global t_object *obj)
{
    if (obj->material.x)
        return (diffuse);
    if (obj->material.y)
        return (specular);
    if (obj->material.z)
        return (refraction);
    if (obj->material.w)
        return (emission);
}

static t_surface   get_surface_properties(global t_object *obj, t_ray r, float t, float m)
{
    t_surface   s;

    s.obj = obj;
    s.pos = r.o + r.d * t;
    s.m = m;
    s.n = find_normal(obj, s.pos, s.m);
    s.nl = (dot(s.n, r.d) < 0) ? s.n : s.n * -1;
    s.material = get_material(obj);
    s.ref = (s.material == emission) ? (float3){0,0,0} : s.obj->color;
    s.maxref = fmax(fmax(s.ref.x, s.ref.y), s.ref.z);
    s.maxref = (s.maxref > 0.75) ? s.maxref * 0.75 : s.maxref;
    return (s);
}

static t_ray   diffuse_reflection(t_surface surf, uint *seeds)
{
    float 	r1, r2, r2s;
    float 	cos_a, sin_a, k;
    float3	w, u, v, d;
    t_ray	rand_ray;

    r1 = 2 * M_PI * get_random(&seeds[0], &seeds[1]);
    r2 = get_random(&seeds[0], &seeds[1]);
    r2s = sqrt(r2);

	w = surf.nl;
	u = normalize(
			cross((fabs(w[0]) > .1f ? (float3)(0, 1, 0) : (float3)(1, 0, 0)), w));
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

static t_ray   specular_reflection(t_surface surf, t_ray r)
{
    t_ray spec;

    spec.o = surf.pos;
    spec.d = r.d - surf.n * 2 * dot(r.d, surf.n);
    return (spec);
}
