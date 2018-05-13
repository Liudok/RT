/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 13:31:55 by skamoza           #+#    #+#             */
/*   Updated: 2018/05/13 16:01:39 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KERNEL_H
# define KERNEL_H

# include <OpenCL/cl.h>

typedef enum	e_obj_type
{
	sphere, plane, cylinder, cone, disk,
	torus, triangle, mobius, bool_substraction,
	bool_intersection, cube, parabaloid, julia,
	second, not_valid
}				t_obj_type;

typedef enum	e_material
{
	diffuse, specular, glass, emission, transparent
}				t_material;

typedef struct	s_sphere
{
	cl_float3		origin;
	cl_float		radius;
	cl_float		r2;
}				t_sphere;

typedef struct	s_plane
{
	cl_float3		origin;
	cl_float3		normal;
}				t_plane;

typedef struct	s_cylinder
{
	cl_float3		origin;
	cl_float3		normal;
	cl_float		radius;
	cl_float		r2;
	cl_float		height;
}				t_cylinder;

typedef struct	s_cone
{
	cl_float3		origin;
	cl_float3		normal;
	cl_float		half_tangent;
	cl_float		m1;
	cl_float		m2;
}				t_cone;

typedef struct	s_disk
{
	cl_float3		origin;
	cl_float3		normal;
	cl_float		radius2;
}				t_disk;

typedef struct	s_torus
{
	cl_float3		origin;
	cl_float3		normal;
	cl_float		big_radius2;
	cl_float		small_radius2;
}				t_torus;

typedef struct	s_triangle
{
	cl_float3		vertex0;
	cl_float3		vertex1;
	cl_float3		vertex2;
}				t_triangle;

typedef struct	s_mobius
{
	cl_float3		origin;
	cl_float		size;
}				t_mobius;

typedef struct	s_cube
{
	cl_float3		min;
	cl_float3		max;
	cl_int			pipes_number;
}				t_cube;

typedef struct	s_parabaloid
{
	cl_float3		origin;
	cl_float3		normal;
	cl_float		radius;
	cl_float		max;
}				t_parabaloid;

typedef struct	s_julia
{
	cl_float4		c;
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
	cl_float	roughness;
	cl_float	ior;
	cl_float3	color;
	cl_uchar4	texture;
}				t_object;

typedef struct	s_camera
{
	cl_float3		base_origin;
	cl_float3		base_dir;
	cl_float3		origin;
	cl_float3		dir;
	cl_float3		cx;
	cl_float3		cy;
	cl_float3		ambient;
	cl_int2			canvas;
	cl_float2		rotate;
}				t_camera;

#endif
