/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saving_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 07:14:14 by skamoza           #+#    #+#             */
/*   Updated: 2018/05/12 07:29:50 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/panels.h"

static void		print_prim_info5(int fd, t_object *o)
{
	if (o->type == 6)
	{
		dprintf(fd, "\t\t\t\"vertex0\": [%f, %f, %f],\n",
				o->prim.triangle.vertex0.s0, o->prim.triangle.vertex0.s1,
				o->prim.triangle.vertex0.s2);
		dprintf(fd, "\t\t\t\"vertex1\": [%f, %f, %f],\n",
				o->prim.triangle.vertex1.s0, o->prim.triangle.vertex1.s1,
				o->prim.triangle.vertex1.s2);
		dprintf(fd, "\t\t\t\"vertex2\": [%f, %f, %f],\n",
				o->prim.triangle.vertex2.s0, o->prim.triangle.vertex2.s1,
				o->prim.triangle.vertex2.s2);
	}
}

static void		print_prim_info4(int fd, t_object *o)
{
	if (o->type == 4)
	{
		dprintf(fd, "\t\t\t\"origin\": [%f, %f, %f],\n",
				o->prim.disk.origin.s0, o->prim.disk.origin.s1,
				o->prim.disk.origin.s2);
		dprintf(fd, "\t\t\t\"normal\": [%f, %f, %f],\n",
				o->prim.disk.normal.s0, o->prim.disk.normal.s1,
				o->prim.disk.normal.s2);
		dprintf(fd, "\t\t\t\"radius2\": %f,\n", o->prim.disk.radius2);
	}
	else if (o->type == 5)
	{
		dprintf(fd, "\t\t\t\"origin\": [%f, %f, %f],\n",
				o->prim.torus.origin.s0, o->prim.torus.origin.s1,
				o->prim.torus.origin.s2);
		dprintf(fd, "\t\t\t\"normal\": [%f, %f, %f],\n",
				o->prim.torus.normal.s0, o->prim.torus.normal.s1,
				o->prim.torus.normal.s2);
		dprintf(fd, "\t\t\t\"big_radius2\": %f,\n",
				o->prim.torus.big_radius2);
		dprintf(fd, "\t\t\t\"small_radius2\": %f,\n",
				o->prim.torus.small_radius2);
	}
	else
		print_prim_info5(fd, o);
}

static void		print_prim_info3(int fd, t_object *o)
{
	if (o->type == 10)
	{
		dprintf(fd, "\t\t\t\"min\": [%f, %f, %f],\n", o->prim.cube.min.s0,
				o->prim.cube.min.s1, o->prim.cube.min.s2);
		dprintf(fd, "\t\t\t\"max\": [%f, %f, %f],\n", o->prim.cube.max.s0,
				o->prim.cube.max.s1, o->prim.cube.max.s2);
		dprintf(fd, "\t\t\t\"pipes_number\": %d,\n",
				o->prim.cube.pipes_number);
	}
	else if (o->type == 11)
	{
		dprintf(fd, "\t\t\t\"origin\": [%f, %f, %f],\n",
				o->prim.parabaloid.origin.s0, o->prim.parabaloid.origin.s1,
				o->prim.parabaloid.origin.s2);
		dprintf(fd, "\t\t\t\"normal\": [%f, %f, %f],\n",
				o->prim.parabaloid.normal.s0, o->prim.parabaloid.normal.s1,
				o->prim.parabaloid.normal.s2);
		dprintf(fd, "\t\t\t\"radius\": %f,\n", o->prim.parabaloid.radius);
		dprintf(fd, "\t\t\t\"max\": %f,\n", o->prim.parabaloid.max);
	}
	else
		print_prim_info4(fd, o);
}

static void		print_prim_info2(int fd, t_object *o)
{
	if (o->type == 3)
	{
		dprintf(fd, "\t\t\t\"origin\": [%f, %f, %f],\n",
				o->prim.cone.origin.s0, o->prim.cone.origin.s1,
				o->prim.cone.origin.s2);
		dprintf(fd, "\t\t\t\"normal\": [%f, %f, %f],\n",
				o->prim.cone.normal.s0, o->prim.cone.normal.s1,
				o->prim.cone.normal.s2);
		dprintf(fd, "\t\t\t\"half_tangent\": %f,\n",
				o->prim.cone.half_tangent);
		dprintf(fd, "\t\t\t\"m1\": %f,\n", o->prim.cone.m1);
		dprintf(fd, "\t\t\t\"m2\": %f,\n", o->prim.cone.m2);
	}
	else if (o->type == 6)
	{
		dprintf(fd, "\t\t\t\"vertex0\": [%f, %f, %f],\n",
				o->prim.triangle.vertex0.s0, o->prim.triangle.vertex0.s1,
				o->prim.triangle.vertex0.s2);
		dprintf(fd, "\t\t\t\"vertex1\": [%f, %f, %f],\n",
				o->prim.triangle.vertex1.s0, o->prim.triangle.vertex1.s1,
				o->prim.triangle.vertex1.s2);
		dprintf(fd, "\t\t\t\"vertex2\": [%f, %f, %f],\n",
				o->prim.triangle.vertex2.s0, o->prim.triangle.vertex2.s1,
				o->prim.triangle.vertex2.s2);
	}
	else
		print_prim_info3(fd, o);
}

void			print_prim_info(int fd, t_object *o)
{
	if (o->type == 0)
	{
		dprintf(fd, "\t\t\t\"origin\": [%f, %f, %f],\n",
			o->prim.sphere.origin.s0, o->prim.sphere.origin.s1,
			o->prim.sphere.origin.s2);
		dprintf(fd, "\t\t\t\"radius\": %f,\n", o->prim.sphere.radius);
	}
	else if (o->type == 1)
	{
		dprintf(fd, "\t\t\t\"origin\": [%f, %f, %f],\n", o->prim.plane.
			origin.s0, o->prim.plane.origin.s1, o->prim.plane.origin.s2);
		dprintf(fd, "\t\t\t\"normal\": [%f, %f, %f],\n", o->prim.plane.
			normal.s0, o->prim.plane.normal.s1, o->prim.plane.normal.s2);
	}
	else if (o->type == 2)
	{
		dprintf(fd, "\t\t\t\"origin\": [%f, %f, %f],\n", o->prim.cylinder.
			origin.s0, o->prim.cylinder.origin.s1, o->prim.cylinder.origin.s2);
		dprintf(fd, "\t\t\t\"normal\": [%f, %f, %f],\n", o->prim.cylinder.
			normal.s0, o->prim.cylinder.normal.s1, o->prim.cylinder.normal.s2);
		dprintf(fd, "\t\t\t\"radius\": %f,\n", o->prim.cylinder.radius);
		dprintf(fd, "\t\t\t\"height\": %f,\n", o->prim.cylinder.height);
	}
	else
		print_prim_info2(fd, o);
}
