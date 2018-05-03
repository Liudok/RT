/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_prim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:04:46 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/03 13:04:50 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/panels.h"

t_primitive			new_sphere(float3 origin, float radius)
{
	t_primitive		prim;

	prim.sphere.origin = origin;
	prim.sphere.radius = radius;
	prim.sphere.r2 = radius * radius;
	return (prim);
}

t_primitive			new_plane(float3 origin, float3 normal)
{
	t_primitive		prim;

	prim.plane.origin = origin;
	prim.plane.normal = normal;
	return (prim);
}

t_primitive			new_cylinder(float3 origin, float3 normal, float radius, float height)
{
	t_primitive		prim;

	prim.cylinder.origin = origin;
	prim.cylinder.normal = normal;
	prim.cylinder.radius = radius;
	prim.cylinder.height = height;
	prim.cylinder.r2 = prim.cylinder.radius * prim.cylinder.radius;
	return (prim);
}

t_primitive			new_cone(float3 origin, float3 normal, float m1, float m2)
{
	t_primitive		prim;

	prim.cone.origin = origin;
	prim.cone.normal = normal;
	prim.cone.m1 = m1;
	prim.cone.m2 = m2;
	prim.cone.half_tangent = 0.5;
	return (prim);
}
