#include "include/kernel.h"

static float sphere_intersect(global t_sphere* obj, t_ray ray) {
	float3 oc;
	float b;
	float dis;
	float t;

	oc = obj->origin - ray.o;
	b = dot(oc, ray.d);
	dis = b * b - dot(oc, oc) + obj->r2;
	if (dis < 0)
		return 0;
	dis = sqrt(dis);
	t = b - dis;
	if (t > EPSILON)
		return t;
	t = b + dis;
	if (t > EPSILON)
		return t;
	return (INFINITY);
}

static float plane_intersect(global t_plane* obj, t_ray ray) {
	float denom;
	float3 oc;

	if ((denom = dot(ray.d, obj->normal)) == 0)
		return (INFINITY);
	oc = ray.o - obj->origin;
	return (-dot(oc, obj->normal) / denom);
}

static float cylinder_intersect(global t_cylinder* obj, t_ray ray, float* m) {
	float a;
	float b;
	float c;
	float3 oc;
	float2 t;

	oc = ray.o - obj->origin;
	t.x = dot(ray.d, normalize(obj->normal));
	t.y = dot(oc, normalize(obj->normal));
	a = dot(ray.d, ray.d) - t.x * t.x;
	b = 2 * (dot(ray.d, oc) - t.x * t.y);
	c = dot(oc, oc) - t.y * t.y - obj->r2;
	ft_roots(&t, a, b, c);
	if ((t.x < 0.0f) && (t.y < 0.0f))
		return (INFINITY);
	if ((t.x < 0.0f) || (t.y < 0.0f)) {
		a = (t.x > t.y) ? t.x : t.y;
		*m = dot(ray.d, normalize(obj->normal)) * a +
			dot(oc, fast_normalize(obj->normal));
		return ((*m <= obj->height) && (*m >= EPSILON) ? t.x : INFINITY);
	}
	a = (t.x < t.y) ? t.x : t.y;
	*m = dot(ray.d, normalize(obj->normal)) * a +
		dot(oc, fast_normalize(obj->normal));
	if ((*m <= obj->height) && (*m >= EPSILON))
		return (a);
	a = (t.x >= t.y) ? t.x : t.y;
	*m = dot(ray.d, normalize(obj->normal)) * a +
		dot(oc, fast_normalize(obj->normal));
	if ((*m <= obj->height) && (*m >= EPSILON))
		return (a);
	return (INFINITY);
}

static float cone_intersect(global t_cone* obj, t_ray ray, float* m) {
	float a;
	float b;
	float c;
	float d;
	float3 oc;
	float2 t;

	oc = ray.o - obj->origin;
	t.x = dot(ray.d, obj->normal);
	t.y = dot(oc, obj->normal);
	d = 1 + obj->half_tangent * obj->half_tangent;
	a = dot(ray.d, ray.d) - d * t.x * t.x;
	b = 2 * (dot(ray.d, oc) - d * t.x * t.y);
	c = dot(oc, oc) - d * t.y * t.y;
	ft_roots(&t, a, b, c);
	if (t.x < 0.0f && t.y < 0.0f)
		return (INFINITY);
	if (t.x < 0.0f || t.y < 0.0f) {
		a = (t.x > t.y) ? t.x : t.y;
		*m = dot(ray.d, obj->normal) * a +
			dot(oc, obj->normal);
		return ((*m <= obj->m2) && (*m >= obj->m1) ? a : INFINITY);
	}
	a = (t.x < t.y) ? t.x : t.y;
	*m = dot(ray.d, obj->normal) * a +
		dot(oc, obj->normal);
	if ((*m <= obj->m2) && (*m >= obj->m1))
		return (a);
	a = (t.x >= t.y) ? t.x : t.y;
	*m = dot(ray.d, obj->normal) * a +
		dot(oc, obj->normal);
	if ((*m <= obj->m2) && (*m >= obj->m1))
		return (a);
	return (INFINITY);
}

static float disk_intersect(global t_disk* obj, t_ray ray) {
	float denom;
	float3 oc;
	float t;
	float3 pos;

	if ((denom = dot(ray.d, obj->normal)) == 0)
		return (INFINITY);
	oc = ray.o - obj->origin;
	t = -dot(oc, obj->normal) / denom;
	if (t < 0)
		return (INFINITY);
	pos = ray.o + t * ray.d;
	pos -= obj->origin;
	if (dot(pos, pos) <= obj->radius2)
		return (t);
	return (INFINITY);
}

static void fourth_degree_equation(float4* t,
		float A,
		float B,
		float C,
		float D,
		float E) {
	float a = -3.0f * B * B / 8.0f / A / A + C / A;
	float b = B * B * B / 8 / A / A / A - B * C / 2 / A / A + D / A;
	float g = -3.0f * B * B * B * B / 256.0f / A / A / A / A +
		C * B * B / 16.0f / A / A / A - B * D / 4.0f / A / A + E / A;
	float P = -a * a / 12.0f - g;
	float Q = -a * a * a / 108.0f + a * g / 3.0f - b * b / 8.0f;
	float R = Q / 2.0f + sqrt(Q * Q / 4.0f + P * P * P / 27.0f);
	float U = cbrt(R);
	float U2 = (U == 0.0f) ? 0.0f : P / 3.0f / U;
	float y = -5.0f / 6.0f * a - U + U2;
	float W = sqrt(a + 2.0f * y);
	t->s0 = -B / 4.0f / A +
		(W + sqrt(-(3.0f * a + 2.0f * y + 2.0f * b / W))) / 2.0f;
	t->s1 = -B / 4.0f / A +
		(W - sqrt(-(3.0f * a + 2.0f * y + 2.0f * b / W))) / 2.0f;
	t->s2 = -B / 4.0f / A +
		(-W + sqrt(-(3.0f * a + 2.0f * y - 2.0f * b / W))) / 2.0f;
	t->s3 = -B / 4.0f / A +
		(-W - sqrt(-(3.0f * a + 2.0f * y - 2.0f * b / W))) / 2.0f;
}

static float torus_intersect(global t_torus* obj, t_ray ray) {
	float3 oc = ray.o - obj->origin;
	float m = dot(ray.d, ray.d);
	float n = dot(ray.d, oc);
	float o = dot(oc, oc);
	float p = dot(ray.d, obj->normal);
	float q = dot(oc, obj->normal);
	float a = m * m;
	float b = 4.0f * m * n;
	float c = 4.0f * n * n + 2.0f * m * o -
		2.0f * (obj->big_radius2 + obj->small_radius2) * m +
		4.0f * obj->big_radius2 * p * p;
	float d = 4.0f * n * o -
		4.0f * (obj->big_radius2 + obj->small_radius2) * n +
		8.0f * obj->big_radius2 * p * q;
	float e = o * o - 2.0f * (obj->big_radius2 + obj->small_radius2) * o +
		4.0f * obj->big_radius2 * q * q +
		(obj->big_radius2 - obj->small_radius2) *
		(obj->big_radius2 - obj->small_radius2);
	float ret = INFINITY;

	float4 t;

	fourth_degree_equation(&t, a, b, c, d, e);
	for (int i = 0; i < 4; i++)
		ret = (t[i] >= EPSILON && t[i] < ret) ? t[i] : ret;
	return (ret);
}

static void intersect(global t_object* obj,
		global t_object** closest,
		t_ray ray,
		float* m,
		float* closest_dist) {
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
		case torus:
			dist = torus_intersect(&obj->prim.torus, ray);
			break;
		default:
			break;
	}
	if (dist <= EPSILON || dist > *closest_dist)
		return;
	*closest_dist = dist;
	*closest = obj;
}
