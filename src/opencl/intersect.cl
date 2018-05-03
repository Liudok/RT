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
	t = native_divide(-dot(oc, obj->normal), denom);
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

static float  triangle_intersect(global t_triangle *obj, t_ray ray)
{
	float	denom;
	float3	oc;
	float3	normal;
	float 	t;
	float3	p;
	float3	edge0;
	float3	edge1;
	float3	edge2;
	float3	c0;
	float3	c1;
	float3	c2;

	edge0 = obj->vertex1 - obj->vertex0;
	edge1 = obj->vertex2 - obj->vertex1;
	edge2 = obj->vertex0 - obj->vertex2;
	normal = normalize(cross(edge0, edge1));

	if ((denom = dot(ray.d, normal)) == 0)
	    return (-1);
	oc = ray.o - obj->vertex0;
	t = -dot(oc, normal) / denom;
	if (t < 0)
	    return (-1);
	p = ray.o + ray.d * t;
	c0 = p - obj->vertex0;
	c1 = p - obj->vertex1;
	c2 = p - obj->vertex2;
	if (dot(normal, cross(edge0, c0)) > 0 && dot(normal, cross(edge1, c1)) > 0 && dot(normal, cross(edge2, c2)) > 0)
	    return (t);
	return (-1);
}

static float	third_degree_equation(float A, float B, float C, float D)
{
    float p = (3.0f * A * C - B * B) / 3.0f/ A / A;
    float q = (2 * B * B * B - 9 * A * B * C + 27.0f * A * A * D) / 27.0f / A / A / A;
    float d = pow(p / 3.0f, 3) + pow(q / 2.0f, 2);
    if (d < 0.0f)
        return (-1);
    float a = cbrt(-q / 2.0f + sqrt(d));
    float b = cbrt(-q / 2.0f - sqrt(d));
    float y = a + b;
    float x = y - B / 3.0f / A;
    return (x);
}

static int dblsgn(float x)
{
    float epsilon = 1e-8;
    return (x < -epsilon) ? (-1) : (x > epsilon);
}

static bool inside(float3 pt, global t_mobius *obj)
{
float epsilon = 1e-8;
	float x = pt.x;
	float y = pt.y;
	float z = pt.z;
	float t = atan2(y, x);
	float s;
	if (dblsgn(sin(t / 2)) != 0)
	{
		s = z / sin(t / 2);
	}
	else
	{
		if (dblsgn(cos(t)) != 0)
		{
			s = (x / cos(t) - obj->radius) / cos(t / 2);
		}
		else
		{
			s = (y / sin(t) - obj->radius) / cos(t / 2);
		}
	}
	x -= (obj->radius + s * cos(t / 2)) * cos(t);
	y -= (obj->radius + s * cos(t / 2)) * sin(t);
	z -= s * sin(t / 2);
	if (dblsgn(x * x + y * y + z * z) != 0)
	{
		return false;
	}
	return (s >= -obj->half_width - epsilon  && s <= obj->half_width + epsilon);
}

static float  mobius_intersect(global t_mobius *obj, t_ray ray)
{
    float epsilon = 1e-8;
    float ox = ray.o.x;
    float oy = ray.o.y;
    float oz = ray.o.z;
    float dx = ray.d.x;
    float dy = ray.d.y;
    float dz = ray.d.z;
    float R = obj->radius;

    float coef_0 = 0;
    float coef_1 = 0;
    float coef_2 = 0;
    float coef_3 = 0;

    coef_0 = ox * ox * oy + oy * oy * oy - 2 * ox * ox * oz - 2 * oy * oy * oz + oy * oz * oz - 2 * ox * oz * R - oy * R * R;
    coef_1 = dy * ox * ox - 2 * dz * ox * ox + 2 * dx * ox * oy + 3 * dy * oy * oy - 2 * dz * oy * oy - 4 * dx * ox * oz - 4 * dy * oy * oz + 2 * dz * oy * oz + dy * oz * oz - 2 * dz * ox * R - 2 * dx * oz * R - dy * R * R;
    coef_2 = 2 * dx * dy * ox - 4 * dx * dz * ox + dx * dx * oy + 3 * dy * dy * oy - 4 * dy * dz * oy + dz * dz * oy - 2 * dx * dx * oz - 2 * dy * dy * oz + 2 * dy * dz * oz - 2 * dx * dz * R;
    coef_3 = dx * dx * dy + dy * dy * dy - 2 * dx * dx * dz - 2 * dy * dy * dz + dy * dz * dz;
    float t = third_degree_equation(coef_3, coef_2, coef_1, coef_0);
    float3 pos = ray.o + t * ray.d;
    if (t > epsilon && inside(pos, obj))
        return (t);
    return (-1);
}

static void swap(float* a, float* b)
{
	float c;
	c = *a;
	*a = *b;
	*b = c;
}

float3	find_normal(global t_object *obj, float3 hit_pos, float m);
static float  cube_intersect(global t_cube *obj, t_ray ray, float* m, global t_object **closest)
{
    float 	t_min;
    float 	t_max;
    float 	t_y_min;
    float 	t_y_max;
    float 	t_z_min;
    float 	t_z_max;
    float2	side = {0, 0};
    float 	t_pipe = MAXFLOAT;

    t_min = (obj->min.x  - ray.o.x) / ray.d.x;
    t_max = (obj->max.x  - ray.o.x) / ray.d.x;
    if (t_min > t_max)
        swap(&t_min, &t_max);
    t_y_min = (obj->min.y  - ray.o.y) / ray.d.y;
    t_y_max = (obj->max.y  - ray.o.y) / ray.d.y;
    if (t_y_min > t_y_max)
        swap(&t_y_min, &t_y_max);
    if (t_min > t_y_max || t_y_min > t_max)
    	return (-1);
    if (t_y_min > t_min)
    {
        side.x = 1;
        t_min = t_y_min;
    }
    if (t_y_max < t_max)
    {
        side.y = 1;
        t_max = t_y_max;
    }
    t_z_min = (obj->min.z - ray.o.z) / ray.d.z;
    t_z_max = (obj->max.z - ray.o.z) / ray.d.z;
    if (t_z_min > t_z_max)
        swap(&t_z_min, &t_z_max);
    if (t_min > t_z_max || t_z_min > t_max)
        return (-1);
    if (t_z_min > t_min)
    {
        side.x = 2;
        t_min = t_z_min;
    }
    if (t_z_max < t_max)
    {
        side.y = 2;
        t_max = t_z_max;
    }

	global t_object *ptr = NULL;
	ptr = (global t_object *)((void *)obj - (void *)&ptr->prim);
	ptr++;
    if (obj->pipes_number)
    {
        int 	i_closet;
        float 	m_current;

        for (int i = 0; i < obj->pipes_number; i++)
        {
            float current = cylinder_intersect(&ptr[i].prim.cylinder, ray, &m_current);
            if (current > EPSILON && current < t_pipe)
            {
                *m = m_current;
                i_closet = i;
                t_pipe = current;
            }
        }
        if (t_pipe < MAXFLOAT)
        {
            float3 pos = ray.o + ray.d * t_pipe;
            float3 normal = find_normal(&ptr[i_closet], pos, *m);
            if (dot(ray.d, normal) > 0.0f)
            {
                *closest = &ptr[i_closet];
                return (t_pipe);
            }
        }
    }
    *closest = NULL;
    if (t_min <= 0)
    {
        *m = side.y;
        t_min = t_max;
    }
    if (t_min > 0)
    {
        float3 pos = ray.o + ray.d * t_min;
		for (int i = 0; i < obj->pipes_number; i++)
        {
            float3 temp = ptr[i].prim.cylinder.origin - pos;
            if (length(temp - dot(temp, ptr[i].prim.cylinder.normal) * ptr[i].prim.cylinder.normal) < ptr[i].prim.cylinder.radius)
            	return (-1);
        }
    }
    *m = side.x;
    return (t_min);
}

static float  sphere_intersect1(t_sphere *obj, t_ray ray, float2* roots)
{
	float	a;
	float	b;
	float	c;
	float3	oc;
	float2	t;

	oc = ray.o - obj->origin;
	a = dot(ray.d, ray.d);
	b = 2 * dot(ray.d, oc);
	c = dot(oc, oc) - (obj->radius * obj->radius);
	ft_roots(&t, a, b, c);
	if (roots)
	*roots = t;
	if ((t.x < 0.0 && t.y >= 0.0) || (t.y < 0.0 && t.x >= 0.0))
	return t.x > t.y ? t.x : t.y;
	else
	return t.x < t.y ? t.x : t.y;
}

static float	bool_substraction_intersect(global t_bool_substraction *obj, t_ray ray,
global t_object **closest)
{
	float2	roots1;
	float2	roots2;
	float 	t1;
	float 	t2;
	global t_object *ptr = NULL;
	ptr = (global t_object *)((void *)obj - (void *)&ptr->prim);
	ptr++;
	t1 = sphere_intersect1((t_sphere *)&ptr->prim.sphere, ray, &roots1);
	ptr++;
	t2 = sphere_intersect1((t_sphere *)&ptr->prim.sphere, ray, &roots2);
	if (t1 <= 0)
		return(-1);
	if (t2 <= 0)
	{
		*closest = --ptr;
		return (t1);
	}
	roots1 = (roots1.x > roots1.y) ? roots1.yx : roots1;
	roots2 = (roots2.x > roots2.y) ? roots2.yx : roots2;
	if (roots1.x < 0)
		return (-1);
	if (roots1.x > roots2.x && roots1.x < roots2.y)
	{
		*closest = ++ptr;
		return (roots2.y);
	}
	*closest = --ptr;
	return (t1);
}

static void intersect(global t_object* obj,
						global t_object** closest,
						t_ray ray,
						float* m,
						float* closest_dist) {
	float dist;
	global t_object *closest_obj;
	float tmp_m = 0;
	switch (obj->type) {
		case sphere:
			dist = sphere_intersect(&obj->prim.sphere, ray);
			break;
		case plane:
			dist = plane_intersect(&obj->prim.plane, ray);
			break;
		case cylinder:
			dist = cylinder_intersect(&obj->prim.cylinder, ray, &tmp_m);
			break;
		case cone:
			dist = cone_intersect(&obj->prim.cone, ray, &tmp_m);
			break;
		case disk:
			dist = disk_intersect(&obj->prim.disk, ray);
			break;
		case torus:
			dist = torus_intersect(&obj->prim.torus, ray);
			break;
		case triangle:
			dist = triangle_intersect(&obj->prim.triangle, ray);
			break;
        case mobius:
            dist = mobius_intersect(&obj->prim.mobius, ray);
            break;
		case cube:
			dist = cube_intersect(&obj->prim.cube, ray, &tmp_m, &closest_obj);
			break;
		case bool_substraction:
			dist = bool_substraction_intersect(&obj->prim.bool_substraction, ray,  &closest_obj);
			break;
		default:
			break;
	}
	if (dist <= EPSILON || dist > *closest_dist)
		return;
	*closest_dist = dist;
	if (obj->type == bool_substraction || obj->type == bool_intersection || (obj->type == cube && closest_obj))
		*closest = closest_obj;
	else
		*closest = obj;
	*m = tmp_m;
}
