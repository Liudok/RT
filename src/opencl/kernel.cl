#define KERNEL_ONLY

#include "include/kernel.h"
#include "src/opencl/utils.cl"
#include "src/opencl/intersect.cl"
#include "src/opencl/surface.cl"

static float3 radiance(global t_object* objs,
		uint objnum,
		t_ray r,
		uint* seeds,
		read_only image2d_array_t textures,
		global uint2 *sizes) {
	int depth = 0;	  // bounces counter
	global t_object* obj;   // intersected object
	float t;		    // distance to hit
	float m;		    // half tangent ?
	float3 accum_col = {0, 0, 0};  // accumulated color
	float3 accum_ref = {1, 1, 1};  // accumulated reflectance
	t_surface surf;	 // surface propertiess

	while (depth < 5000)
	{
		obj = NULL;
		t = MAXFLOAT;

		for (uint i = 0; i < objnum; i++)
			intersect(&objs[i], &obj, r, &m, &t);
		if (!obj || t >= MAXFLOAT || t < EPSILON)
			break;

        surf = get_surface_properties(obj, r, t, m, textures, sizes, seeds);
        if (surf.material == emission)
			surf.emission = surf.ref;
        accum_col += accum_ref * surf.emission;

        if (++depth > 5)
        {
            if (get_random(&seeds[0], &seeds[1]) >= surf.maxref)
                break;
            surf.ref /= surf.maxref;
        }
		accum_ref *= surf.ref;
        if (surf.material == specular)
            r = specular_reflection(surf, r);
		else if (surf.material == transparent)
			r.o = surf.pos;
		else
            r = diffuse_reflection(surf, seeds);
    }
    return (clamp(accum_col, 0.f, 1.0f));
}

static t_ray initRay(int2 coords, uint2 sub, t_camera cam, uint* seeds) {
	t_ray ray;
	float3 dir;
	float r1 = 2 * get_random(&seeds[0], &seeds[1]);
	float r2 = 2 * get_random(&seeds[0], &seeds[1]);
	float dx = (r1 < 1) ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
	float dy = (r2 < 1) ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);

    dx = ((sub.x + 0.5f + dx) / 2.0f + coords.x) / (float)cam.canvas.x - 0.5f;
    dy = ((sub.y + 0.5f + dy) / 2.0f + coords.y) / (float)cam.canvas.y - 0.5f;
    dir = cam.cx * dx + cam.cy * dy + cam.dir;

    ray.d = normalize(dir);
    ray.o = cam.origin;
    return (ray);
}

__kernel __attribute__((vec_type_hint(float3)))
void path_tracing(
		global t_object* objs,
		uint objnum,
		t_camera camera,
		global uint* input_seeds,
		global float3* colors,
		uint currentSample,
		read_only image2d_array_t textures,
		global uint2 *sizes) {
	int i = get_global_id(0);
	int2 coords = {i % camera.canvas.x, i / camera.canvas.x};
	uint seeds[2];
	float3 rad = {0, 0, 0};
	t_ray ray;

    seeds[0] = input_seeds[i * 2];
    seeds[1] = input_seeds[i * 2 + 1];
    // Each pixel divide by 4 sub-pixels
    for (uint sy = 0; sy < 2; sy++)
    {
        for (uint sx = 0; sx < 2; sx++)
        {
            // Init ray dir on 'table tent' term
            ray = initRay(coords, (uint2)(sx, sy), camera, seeds);
            // Compute sub-pixel radiance and save, divide by 4
            rad += radiance(objs, objnum, ray, seeds, textures, sizes) * 0.25f;
        }
    }
    add_sample(colors, rad, currentSample, i);

	input_seeds[i * 2] = seeds[0];
	input_seeds[i * 2 + 1] = seeds[1];
}


__kernel __attribute__((vec_type_hint(float3)))
void mouse_hook( global t_object* objs, uint objnum, t_camera camera, uint2 coords, global int *ret)
{
	t_ray ray;

	float dx = (0.5f + coords.x) / (float)camera.canvas.x - 0.5f;
	float dy = (0.5f + coords.y) / (float)camera.canvas.y - 0.5f;
	float3 dir = camera.cx * dx + camera.cy * dy + camera.dir;

	ray.d = normalize(dir);
	ray.o = camera.origin + dir;

	global t_object* obj = NULL;

	float m;
	float t = INFINITY;
	for (uint i = 0; i < objnum; i++)
		intersect(&objs[i], &obj, ray, &m, &t);

	if (obj && t < INFINITY)
		*ret = obj - objs;
	else
		*ret = -1;
}

__kernel __attribute__((vec_type_hint(float3)))
void after_effects(global float3 *colors, global int *pixels, int type, t_camera camera)
{
	int i = get_global_id(0);
	int2 coords = {i % camera.canvas.x, i / camera.canvas.x};
	float3 current_pixel;
switch (type) {
		case 1:
			current_pixel = blur(colors, camera.canvas, coords);
			break;
		case 2:
			current_pixel = negative(colors[i]);
			break;
		case 3:
			current_pixel = sepia(colors[i]);
			break;
		case 4:
			current_pixel = cartoon(colors, camera.canvas, coords);
			break;
		case 5:
			current_pixel = black_white(colors[i]);
			break;
		default:
			current_pixel = colors[i];
	}
    put_pixel(pixels, current_pixel, i);
}
