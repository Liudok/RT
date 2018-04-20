/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 13:31:55 by skamoza           #+#    #+#             */
/*   Updated: 2018/03/27 11:53:56 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KERNEL_H
# define KERNEL_H

# ifndef NULL
#  define NULL ((void *)0)
# endif

# define EPSILON 1e-3

# ifndef KERNEL_ONLY
#  define float cl_float
#  define float3 cl_float3
#  define float4 cl_float4
#  define uint	cl_uint
#  define int2	cl_int2
# endif

# define PUT_PIXEL(p, w, x, y, c) (p[y * w + x] = toInt(c))

typedef unsigned char	t_uchar;

typedef union	u_color
{
	t_uchar		byte[4];
	int			val;
}				t_color;

typedef enum	e_obj_type
{
	sphere, plane, cylinder, cone, disk, not_valid
}				t_obj_type;

typedef enum	e_material
{
	diffuse, specular, refraction, emission
}				t_material;

typedef struct	s_sphere
{
	float3		origin;
	float		radius;
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

typedef	union	u_primitive
{
	t_plane		plane;
	t_sphere	sphere;
	t_cylinder	cylinder;
	t_cone		cone;
	t_disk		disk;
}				t_primitive;

typedef struct	s_object
{
	float4		material;
	float3		color;
	t_obj_type	type;
	t_primitive	prim;
	uint 		texture;
}				t_object;

typedef struct	s_camera
{
	float3		origin;
	float3		dir;
	float3		cx;
	float3		cy;
	int2		canvas;
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
	constant t_object	*obj;
	t_material			material;
	float				maxref;
	float3				pos;
	float3				n;
	float3				nl;
	float3				f;
}						t_surface;

typedef struct			s_ray
{
	float3				o;
	float3				d;
}						t_ray;

# endif

#endif
