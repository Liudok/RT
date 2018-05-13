/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_prim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:04:46 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/10 17:17:52 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/panels.h"

t_primitive			new_sphere(cl_float3 origin, float radius)
{
	t_primitive		prim;

	prim.sphere.origin = origin;
	prim.sphere.radius = radius;
	prim.sphere.r2 = radius * radius;
	return (prim);
}

t_primitive			new_plane(cl_float3 origin, cl_float3 normal)
{
	t_primitive		prim;

	prim.plane.origin = origin;
	prim.plane.normal = normal;
	return (prim);
}

t_primitive			new_cylinder(cl_float3 origin, cl_float3 n, float r,
						float h)
{
	t_primitive		prim;

	prim.cylinder.origin = origin;
	prim.cylinder.normal = n;
	prim.cylinder.radius = r;
	prim.cylinder.height = h;
	prim.cylinder.r2 = prim.cylinder.radius * prim.cylinder.radius;
	return (prim);
}

t_primitive			new_cone(cl_float3 origin, cl_float3 n, float m1, float m2)
{
	t_primitive		prim;

	prim.cone.origin = origin;
	prim.cone.origin.x = prim.cone.origin.x * (-1);
	prim.cone.normal = n;
	prim.cone.m1 = m1;
	prim.cone.m2 = m2;
	prim.cone.half_tangent = 0.5;
	return (prim);
}

t_primitive			new_disk(cl_float3 origin, cl_float3 normal, float radius)
{
	t_primitive		prim;

	prim.disk.origin = origin;
	prim.disk.normal = normal;
	prim.cylinder.radius = radius;
	return (prim);
}
