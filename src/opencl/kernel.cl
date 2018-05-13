# define EPSILON 1e-3f
# ifndef M_PI
#  define M_PI 3.141595f
# endif
# ifndef NULL
#  define NULL ((void *)0)
# endif

typedef enum	e_obj_type
{
	sphere, plane, cylinder, cone, disk,
	torus, triangle, mobius, bool_substraction,
	bool_intersection, cube, parabaloid, julia,
	second,	not_valid
}				t_obj_type;

typedef enum	e_material
{
	diffuse, specular, glass, emission, transparent
}				t_material;

typedef struct	s_sphere
{
	float3		origin;
	float		radius;
	float		r2;
}				t_sphere;

typedef struct	s_plane
{
	float3		origin;
	float3		normal;
}				t_plane;

typedef struct	s_cylinder
{
	float3		origin;
	float3		normal;
	float		radius;
	float		r2;
	float 		height;
}				t_cylinder;

typedef struct	s_cone
{
	float3		origin;
	float3		normal;
	float 		half_tangent;
	float 		m1;
	float 		m2;
}				t_cone;

typedef struct	s_disk
{
	float3		origin;
	float3		normal;
	float 		radius2;
}				t_disk;

typedef struct	s_torus
{
	float3		origin;
	float3		normal;
	float 		big_radius2;
	float 		small_radius2;
}				t_torus;

typedef struct	s_triangle
{
	float3		vertex0;
	float3		vertex1;
	float3		vertex2;
}				t_triangle;

typedef struct	s_mobius
{
	float3 		origin;
	float 		size;
}				t_mobius;

typedef struct	s_cube
{
	float3		min;
	float3		max;
	int 		pipes_number;
}				t_cube;

typedef struct	s_parabaloid
{
	float3		origin;
	float3		normal;
	float 		radius;
	float 		max;
}				t_parabaloid;

typedef struct	s_julia
{
	float4		c;
}				t_julia;

typedef	union	u_primitive
{
	t_plane			plane;
	t_sphere		sphere;
	t_cylinder		cylinder;
	t_cone			cone;
	t_disk			disk;
	t_torus			torus;
	t_triangle		triangle;
	t_mobius		mobius;
	t_cube			cube;
	t_parabaloid	parabaloid;
	t_julia			julia;
}				t_primitive;

typedef struct	s_object
{
	t_obj_type	type;
	t_primitive	prim;
	t_material	material;
	float		roughness;
	float		ior;
	float3		color;
	uchar4 		texture;
}				t_object;

typedef struct	s_camera
{
	float3		base_origin;
	float3 		base_dir;
	float3		origin;
	float3		dir;
	float3		cx;
	float3		cy;
	float3		ambient;
	int2		canvas;
	float2 		rotate;
}				t_camera;

typedef struct			s_surface
{
	global t_object		*obj;
	t_material			material;
	float				maxref;
	float3				pos;
	float3				emission;
	float3				n;
	float3				nl;
	float3				f;
	float3				ref;
	float2				uv;
	float 				m;
	float 				ior;
}						t_surface;

typedef struct			s_ray
{
	float3				o;
	float3				d;
}						t_ray;

typedef	struct			s_equation
{
	bool				flag;
	float				aa;
	float				pp;
	float				rr;
	float				q2;
	float				c;
	float				b;
	float				br;
	float				discr;
	float				real1;
	float				real2;
	float				im1;
	float				im2;
	float2				l;
}						t_equation;

#include "src/opencl/utils.cl"
#include "src/opencl/julia.cl"
#include "src/opencl/intersect.cl"
#include "src/opencl/surface.cl"

static float3 radiance(global t_object* objs,
		const uint objnum,
		t_ray r,
		uint* seeds,
		read_only image2d_array_t textures,
		global uint2 *sizes,
		const float3 ambient) {
	int depth = 0;	  // bounces counter
	global t_object* obj;   // intersected object
	float t;		    // distance to hit
	float m;		    // half tangent ?
	float total_dist = 0;   // total distance
	float3 accum_col = {0, 0, 0};  // accumulated color
	float3 accum_ref = {1, 1, 1};  // accumulated reflectance
	t_surface surf;	 // surface propertiess

	while (true)
	{
		obj = NULL;
		t = MAXFLOAT;

		for (uint i = 0; i < objnum; i++)
			intersect(&objs[i], &obj, r, &m, &t);
		if (!obj || t >= MAXFLOAT || t < EPSILON)
			break;
		
		total_dist += t;
        surf = get_surface_properties(obj, r, t, m, textures, sizes, seeds);
        if (surf.material == emission)
			surf.emission = surf.ref;
        accum_col += (accum_ref * surf.emission) / cbrt(cbrt(total_dist));

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
		else if (surf.material == glass)
			r = glass_refraction(surf, r, seeds, &accum_ref);
		else
			r = diffuse_reflection(surf, seeds);
		if (depth > 5000)
			break;
    }
    return max(accum_col, accum_ref * ambient);
}

static t_ray initRay(const int2 coords, const uchar2 sub, const t_camera cam, uint* seeds) {
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
		const t_camera camera,
		global uint* input_seeds,
		global float3* colors,
		const uint currentSample,
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
    for (uchar sy = 0; sy < 2; sy++)
    {
        for (uchar sx = 0; sx < 2; sx++)
        {
            // Init ray dir on 'table tent' term
            ray = initRay(coords, (uchar2)(sx, sy), camera, seeds);
#ifdef STEREO
		ray.o += (sy ? camera.cx * 0.1f : 0);
#endif
            // Compute sub-pixel radiance and save, divide by 4
            rad += radiance(objs, objnum, ray, seeds, textures, sizes, camera.ambient)
#ifdef STEREO
	*			(sy ? (float3)(1,0.5,0) : (float3)(0,0.5,1))
#endif
				* 0.25f;
        }
    }
	/*
	uint sy = (currentSample % 4) / 2);
	uint sx = currentSample % 2;
	ray = initRay(coords, (uint2)(sx, sy), camera, seeds);
	rad = radiance(objs, objnum, ray, seeds, textures, sizes, camera.ambient);
	*/
    add_sample(colors, clamp(rad, 0, 1.0f), currentSample, i);

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
	switch (type) {
		case 1:
			return put_pixel(pixels, blur(colors, camera.canvas, coords), i);
		case 2:
			return put_pixel(pixels, negative(colors[i]), i);
		case 3:
			return put_pixel(pixels, sepia(colors[i]), i);
		case 4:
			return put_pixel(pixels, cartoon(colors, camera.canvas, coords), i);
		case 5:
			return put_pixel(pixels, black_white(colors[i]), i);
		default:
			return put_pixel(pixels, colors[i], i);
	}
}
