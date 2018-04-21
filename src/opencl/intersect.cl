
#include "include/kernel.h"

static float  sphere_intersect(global t_sphere *obj, t_ray ray)
{
	// float	a;
	// float	b;
	// float	c;
	// float3	oc;
	// float2	t;

	// oc = ray.o - obj->origin;
	// a = dot(ray.d, ray.d);
	// b = 2 * dot(ray.d, oc);
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

	oc = obj->origin - ray.o;
	b = dot(oc, ray.d);
	dis = b * b - dot(oc, oc) + obj->r2;
	if (dis < 0)
		return 0;
	dis = sqrt(dis);
	return ((t = b - dis) > EPSILON) ? t : ((t = b + dis) > EPSILON) ? t : 0;
}

static float  plane_intersect(global t_plane *obj, t_ray ray)
{
	float	denom;
	float3	oc;

	if ((denom = dot(ray.d, obj->normal)) == 0)
		return (-1);
	oc = ray.o - obj->origin;
	return (-dot(oc, obj->normal) / denom);
}

static float  cylinder_intersect(global t_cylinder *obj, t_ray ray, float *m)
{
	float	a;
	float	b;
	float	c;
	float3	oc;
	float2	t;

	oc = ray.o - obj->origin;
	t.x = dot(ray.d, normalize(obj->normal));
	t.y = dot(oc, normalize(obj->normal));
	a = dot(ray.d, ray.d) - t.x * t.x;
	b = 2 * (dot(ray.d, oc) - t.x * t.y);
	c = dot(oc, oc) - t.y * t.y - obj->r2;
	ft_roots(&t, a, b, c);
	if ((t.x  < 0.0f) && (t.y < 0.0f))
		return (-1);
	if ((t.x  < 0.0f) || (t.y < 0.0f))
	{
		a = (t.x > t.y) ? t.x : t.y;
		*m  = dot(ray.d, normalize(obj->normal)) * a + dot(oc, fast_normalize(obj->normal));
		return ((*m <= obj->height) && (*m >= 0) ? t.x : -1);
	}
	a = (t.x < t.y) ? t.x : t.y;
	*m  = dot(ray.d, normalize(obj->normal)) * a + dot(oc, fast_normalize(obj->normal));
	if ((*m <= obj->height) && (*m >= 0))
		return (a);
	a = (t.x >= t.y) ? t.x : t.y;
	*m  = dot(ray.d, normalize(obj->normal)) * a + dot(oc, fast_normalize(obj->normal));
	if ((*m <= obj->height) && (*m >= 0))
		return (a);
	return (-1);
}

static float  cone_intersect(global t_cone *obj, t_ray ray, float *m)
{
	float	a;
	float	b;
	float	c;
	float 	d;
	float3	oc;
	float2	t;

	oc = ray.o - obj->origin;
	t.x = dot(ray.d, normalize(obj->normal));
	t.y = dot(oc, normalize(obj->normal));
	d = 1 + obj->half_tangent * obj->half_tangent;
	a = dot(ray.d, ray.d) - d * t.x * t.x;
	b = 2 * (dot(ray.d, oc) - d * t.x * t.y);
	c = dot(oc, oc) - d * t.y * t.y;
	ft_roots(&t, a, b, c);
	if ((t.x  < 0.0f) && (t.y < 0.0f))
		return (-1);
	if ((t.x  < 0.0f) || (t.y < 0.0f))
	{
		a = (t.x > t.y) ? t.x : t.y;
		*m  = dot(ray.d, normalize(obj->normal)) * a + dot(oc, fast_normalize(obj->normal));
		return ((*m <= obj->m2) && (*m >= obj->m1) ? t.x : -1);
	}
	a = (t.x < t.y) ? t.x : t.y;
	*m  = dot(ray.d, normalize(obj->normal)) * a + dot(oc, fast_normalize(obj->normal));
	if ((*m <= obj->m2) && (*m >= obj->m1))
		return (a);
	a = (t.x >= t.y) ? t.x : t.y;
	*m  = dot(ray.d, normalize(obj->normal)) * a + dot(oc, fast_normalize(obj->normal));
	if ((*m <= obj->m2) && (*m >= obj->m1))
		return (a);
	return (-1);
}

static float  disk_intersect(global t_disk *obj, t_ray ray)
{
	float	denom;
	float3	oc;
	float	t;
	float3 	pos;

	if ((denom = dot(ray.d, obj->normal)) == 0)
		return (-1);
	oc = ray.o - obj->origin;
	t = -dot(oc, obj->normal) / denom;
	if (t < 0)
		return (-1.0f);
	pos = ray.o + t * ray.d;
	pos -= obj->origin;
	if (dot(pos, pos) <= obj->radius2)
		return (t);
	return (-1);
}

static void		intersect(	global t_object *obj,
							global t_object **closest,
							t_ray			ray,
							float 			*m,
							float			*closest_dist)
{
	float dist;
	switch (obj->type) {
		case sphere:
			dist = sphere_intersect(&obj->prim.sphere, ray);
			break;
		case plane:
			dist = plane_intersect(&obj->prim.plane, ray);
			break;
		case cylinder:
			dist = cylinder_intersect(&obj->prim.cylinder, ray, m);
			break;
		case cone:
			dist = cone_intersect(&obj->prim.cone, ray, m);
			break;
		case disk:
			dist = disk_intersect(&obj->prim.disk, ray);
			break;
		default:
			break;
	}
	if (dist <= 0 || dist > *closest_dist)
		return ;
	*closest_dist = dist;
	*closest = obj;
}
