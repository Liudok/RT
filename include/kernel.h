/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 13:31:55 by skamoza           #+#    #+#             */
/*   Updated: 2018/04/27 12:41:42 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KERNEL_H
# define KERNEL_H

# ifndef NULL
#  define NULL ((void *)0)
# endif

# define EPSILON 1e-3
# ifndef M_PI
#  define M_PI 3.141595f
# endif
# ifndef KERNEL_ONLY
#  define float cl_float
#  define float2 cl_float2
#  define float3 cl_float3
#  define float4 cl_float4
#  define uchar4 cl_uchar4
#  define uint	cl_uint
#  define int2	cl_int2
# endif

typedef enum	e_obj_type
{
	sphere, plane, cylinder, cone, disk,
	torus,
	triangle,
	mobius,
	bool_substraction,
	bool_intersection,
	cube,
	not_valid
}				t_obj_type;

typedef enum	e_material
{
	diffuse, specular, refraction, emission, transparent
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
	float 		radius;
	float 		half_width;
}				t_mobius;

typedef struct	s_bool_substraction
{
	struct s_object	*obj1;
	struct s_object	*obj2;
}				t_bool_substraction;

//typedef struct	s_bool_intersection
//{
//	const __constant	struct s_object	*obj1;
//	const __constant	struct s_object	*obj2;
//}				t_bool_intersection;
//
typedef struct	s_cube
{
	float3		min;
	float3		max;
	int 		pipes_number;
	struct s_object	*objs;
}				t_cube;

typedef	union	u_primitive
{
	t_plane		plane;
	t_sphere	sphere;
	t_cylinder	cylinder;
	t_cone		cone;
	t_disk		disk;
	t_torus		torus;
	t_triangle	triangle;
	t_mobius	mobius;
	t_bool_substraction bool_substraction;
//	t_bool_intersection bool_intersection;
	t_cube		cube;
}				t_primitive;

typedef struct	s_object
{
	t_obj_type	type;
	t_primitive	prim;
	float4		material;
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
	int2		canvas;
	float2 		rotate;
}				t_camera;

# ifdef KERNEL_ONLY

typedef struct			s_hit
{
	float3				pos;
	float3				normal;
	float 				m;
	float3				old_dir;
	float3				mask;
	float3				color;
	float3				color_accum;
	unsigned long		samples;
	constant t_object	*object;
	uint				seeds[2];
	unsigned char		iterations;
	t_material			material;
}						t_hit;

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
}						t_surface;

typedef struct			s_ray
{
	float3				o;
	float3				d;
}						t_ray;

# endif

#endif
