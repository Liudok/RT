/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 13:31:55 by skamoza           #+#    #+#             */
/*   Updated: 2018/05/11 20:49:37 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KERNEL_H
# define KERNEL_H

# ifndef NULL
#  define NULL ((void *)0)
# endif

# define EPSILON 1e-3f
# ifndef M_PI
#  define M_PI 3.141595f
# endif
# ifndef KERNEL_ONLY
#  include <OpenCL/cl.h>
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

# ifdef KERNEL_ONLY

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

# endif

#endif
