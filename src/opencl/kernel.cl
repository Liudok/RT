#define KERNEL_ONLY

#include "include/kernel.h"
#include "src/opencl/utils.cl"
#include "src/opencl/intersect.cl"
#include "src/opencl/surface.cl"

static float3 radiance(global t_object* objs,
		uint objnum,
		t_ray r,
		uint* seeds,
		read_only image3d_t textures) {
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

        surf = get_surface_properties(obj, r, t, m, textures);
        accum_col += (surf.material == emission) ? accum_ref * obj->color : 0;

        if (++depth > 5)
        {
            if (get_random(&seeds[0], &seeds[1]) >= surf.maxref)
                break;
            surf.ref /= surf.maxref;
        }
		accum_ref *= surf.ref;
        if (surf.material == diffuse || surf.material == emission)
            r = diffuse_reflection(surf, seeds);
        else if (surf.material == specular)
            r = specular_reflection(surf, r);

    }
    return (clamp(accum_col, 0.f, 1.0f));
}

static t_ray initRay(uint2 coords, uint2 sub, t_camera cam, uint* seeds) {
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
    ray.o = cam.origin + dir;
    return (ray);
}

__kernel __attribute__((vec_type_hint(float3)))
void path_tracing(
		global t_object* objs,
		uint objnum,
		t_camera camera,
		global uint* inputSeeds,
		global float3* colors,
		global int* pixels_mem,
		uint currentSample,
		read_only image3d_t textures) {
	int i = get_global_id(0);
	uint2 coords = {i % camera.canvas.x, i / camera.canvas.x};
	uint seeds[2];
	float3 rad = {0, 0, 0};
	t_ray ray;

    seeds[0] = inputSeeds[i * 2];
    seeds[1] = inputSeeds[i * 2 + 1];
    // Each pixel divide by 4 sub-pixels
    for (uint sy = 0; sy < 2; sy++)
    {
        for (uint sx = 0; sx < 2; sx++)
        {
            // Init ray dir on 'table tent' term
            ray = initRay(coords, (uint2)(sx, sy), camera, seeds);
            // Compute sub-pixel radiance and save, divide by 4
            rad += radiance(objs, objnum, ray, seeds, textures) * 0.25f;
        }
    }
    addSample(colors, &rad, currentSample, i);
    putPixel(pixels_mem, colors, i);

	inputSeeds[i * 2] = seeds[0];
	inputSeeds[i * 2 + 1] = seeds[1];
}
