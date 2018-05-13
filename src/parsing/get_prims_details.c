/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prims_details.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 11:41:26 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/11 12:27:24 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void		get_primitives_details2(t_object *o, char *n,
									struct _json_value *val)
{
	if (o->type == cone)
	{
		o->prim.cone.origin = !ft_strncmp(n, "origin", 6) ?
							get_float3(val) : o->prim.cone.origin;
		o->prim.cone.normal = !ft_strncmp(n, "normal", 6) ?
							get_float3(val) : o->prim.cone.normal;
		o->prim.cone.half_tangent = !ft_strncmp(n, "half_tangent", 6) ?
							get_number(val) : o->prim.cone.half_tangent;
		o->prim.cone.m1 = !ft_strncmp(n, "m1", 2) ?
							get_number(val) : o->prim.cone.m1;
		o->prim.cone.m2 = !ft_strncmp(n, "m2", 2) ?
							get_number(val) : o->prim.cone.m2;
	}
	else if (o->type == disk)
	{
		o->prim.disk.origin = !ft_strncmp(n, "origin", 6) ?
								get_float3(val) : o->prim.disk.origin;
		o->prim.disk.normal = !ft_strncmp(n, "normal", 6) ?
								get_float3(val) : o->prim.disk.normal;
		o->prim.disk.radius2 = !ft_strncmp(n, "radius2", 7) ?
								get_number(val) : o->prim.disk.radius2;
	}
}

void		get_primitives_details3(t_object *o, char *n,
									struct _json_value *val)
{
	if (o->type == torus)
	{
		o->prim.torus.origin = !ft_strncmp(n, "origin", 6) ?
							get_float3(val) : o->prim.torus.origin;
		o->prim.torus.normal = !ft_strncmp(n, "normal", 6) ?
							get_float3(val) : o->prim.torus.normal;
		o->prim.torus.big_radius2 = !ft_strncmp(n, "big_radius2", 11) ?
							get_number(val) : o->prim.torus.big_radius2;
		o->prim.torus.small_radius2 = !ft_strncmp(n, "small_radius2", 13) ?
							get_number(val) : o->prim.torus.small_radius2;
	}
	else if (o->type == mobius)
	{
		o->prim.mobius.origin = !ft_strncmp(n, "origin", 6) ?
							get_float3(val) : o->prim.mobius.origin;
		o->prim.mobius.size = !ft_strncmp(n, "size", 4) ?
							get_number(val) : o->prim.mobius.size;
	}
}

void		get_primitives_details4(t_object *o, char *n,
									struct _json_value *val)
{
	if (o->type == triangle)
	{
		o->prim.triangle.vertex0 = !ft_strncmp(n, "vertex0", 7) ?
								get_float3(val) : o->prim.triangle.vertex0;
		o->prim.triangle.vertex1 = !ft_strncmp(n, "vertex1", 7) ?
								get_float3(val) : o->prim.triangle.vertex1;
		o->prim.triangle.vertex2 = !ft_strncmp(n, "vertex2", 7) ?
								get_float3(val) : o->prim.triangle.vertex2;
	}
	else if (o->type == cube)
	{
		o->prim.cube.max = !ft_strncmp(n, "max", 3) ?
						get_float3(val) : o->prim.cube.max;
		o->prim.cube.min = !ft_strncmp(n, "min", 3) ?
						get_float3(val) : o->prim.cube.min;
		o->prim.cube.pipes_number = !ft_strncmp(n, "pipes_number", 12) ?
						get_number(val) : o->prim.cube.pipes_number;
	}
}

void		get_primitives_details5(t_object *o, char *n,
									struct _json_value *val)
{
	if (o->type == parabaloid)
	{
		o->prim.parabaloid.origin = !ft_strncmp(n, "origin", 6) ?
							get_float3(val) : o->prim.parabaloid.origin;
		o->prim.parabaloid.normal = !ft_strncmp(n, "normal", 6) ?
							get_float3(val) : o->prim.parabaloid.normal;
		o->prim.parabaloid.max = !ft_strncmp(n, "max", 3) ?
							get_number(val) : o->prim.parabaloid.max;
		o->prim.parabaloid.radius = !ft_strncmp(n, "radius", 6) ?
							get_number(val) : o->prim.parabaloid.radius;
	}
	else if (o->type == julia)
	{
		o->prim.julia.c = !ft_strcmp(n, "c") ?
							get_float4(val) : o->prim.julia.c;
	}
}
