
#include "include/kernel.h"

static float3	sphere_normal(global t_sphere *obj, float3 pos)
{
	return (normalize(pos - obj->origin));
}

static float3	plane_normal(global t_plane *obj)
{
	return (obj->normal);
}

static float3	cylinder_normal(global t_cylinder *obj, float3 pos, float m)
{
	return (normalize(pos - obj->origin - obj->normal * m));
}

static float3	cone_normal(global t_cone *obj, float3 pos, float m)
{
	return (normalize(pos - obj->origin - (1 + obj->half_tangent * obj->half_tangent)) * obj->normal * m);
}

static float3	disk_normal(global t_disk *obj)
{
	return (obj->normal);
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
	else if (obj->material.y)
        return (specular);
    else if (obj->material.z)
        return (refraction);
    else if (obj->material.w)
        return (emission);
	return (diffuse);
}

static void map_normal(read_only image3d_t textures,
						 t_surface *surf, uint2 size)
{
	float3 map_n = normalize(get_texel(textures, surf, surf->obj->tex.y, size));
	float3 t = cross(surf->n, (float3)(0.f, 1.f, 0.f));
	if (fast_length(t) == 0.f)
		t = cross(surf->n, (float3)(0.f, 0.f, 1.f));
	t = normalize(t);
	float3 b = cross(surf->n, t);
	surf->n = normalize(t * map_n.x
					+ b * map_n.y + surf->n * map_n.z);
}

static void map_light(read_only image3d_t textures,
						 t_surface *surf, uint2 size)
{
	float3 map_n = get_texel(textures, surf, surf->obj->tex.y, size);
	if (fast_length(map_n) > 0.2)
		surf->material = emission;
}

static float3 apply_textures(t_surface *surf, read_only image3d_t textures, uint2 *sizes)
{
	uint4 tex = surf->obj->textures;
	surf.uv = get_tex_coords(surf);

	if (tex.y && tex.y <= NUM_TEX) //normal_map
		map_normal(textures, surf, sizes[tex.y]);
	if (tex.z && tex.z <= NUM_TEX) //light map
		map_light(textures, surf, sizes[tex.z]);
	if (tex.x == 255)
		return (return (surf.nl * .49f + .5f));
	if (tex.x && tex.x <= NUM_TEX)
		return (get_texel(textures, surf, tex.x, size[tex.x]));
	return ((float3)(.9f, .9f, .9f));
}

static t_surface   get_surface_properties(global t_object *obj,
		t_ray r, float t, float m, read_only image3d_t textures, uint2 *sizes)
{
    t_surface   s;

    s.obj = obj;
    s.pos = r.o + r.d * t;
    s.m = m;
    s.n = find_normal(obj, s.pos, s.m);
    s.nl = (dot(s.n, r.d) < 0) ? s.n : s.n * -1;
    s.material = get_material(obj);
	s.ref = (s.material == emission) ?
		(float3){0,0,0} : apply_textures(&s, textures, sizes);
	/*
	// Using normal as texture. Really pretty.
	s.ref = s.nl * 2.f + 0.5f;
	 */
    s.maxref = fmax(fmax(s.ref.x, s.ref.y), s.ref.z);
    s.maxref -= (s.maxref > 0.75) ? (s.maxref - 0.75) * 0.75 : 0;
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
	u = normalize(cross((fabs(w[0]) > .1f ?
					(float3)(0, 1, 0) : (float3)(1, 0, 0)), w));
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
