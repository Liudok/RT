/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 19:00:50 by lberezyn          #+#    #+#             */
/*   Updated: 2018/04/25 12:44:19 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/parser.h"

void				get_primitives_details2(t_object *o, char *n, struct _json_value *val)
{
	if (o->type == cone)
	{
		o->prim.cone.origin = !ft_strncmp(n, "origin", 6) ? get_float3(val) : o->prim.cone.origin;
		o->prim.cone.normal = !ft_strncmp(n, "normal", 6) ? get_float3(val) : o->prim.cone.normal;
		o->prim.cone.half_tangent = !ft_strncmp(n, "half_tangent", 6) ? get_number(val) : o->prim.cone.half_tangent;
		o->prim.cone.m1 = !ft_strncmp(n, "m1", 2) ? get_number(val) : o->prim.cone.m1;
		o->prim.cone.m2 = !ft_strncmp(n, "m2", 2) ? get_number(val) : o->prim.cone.m2;
	}
	if (o->type == disk)
	{
		o->prim.disk.origin = !ft_strncmp(n, "origin", 6) ? get_float3(val) : o->prim.disk.origin;
		o->prim.disk.normal = !ft_strncmp(n, "normal", 6) ? get_float3(val) : o->prim.disk.normal;
		o->prim.disk.radius2 = !ft_strncmp(n, "radius2", 7) ? get_number(val) : o->prim.disk.radius2;
	}
}

void				get_primitives_details(t_object *o, char *n, struct _json_value *val)
{
	if (o->type == plane)
	{
		o->prim.plane.origin = !ft_strncmp(n, "origin", 6) ? get_float3(val) : o->prim.plane.origin;
		o->prim.plane.normal = !ft_strncmp(n, "normal", 6) ? get_float3(val) : o->prim.plane.normal;
	}
	else if (o->type == sphere)
	{
		o->prim.sphere.origin = !ft_strncmp(n, "origin", 6) ? get_float3(val) : o->prim.sphere.origin;
		o->prim.sphere.radius = !ft_strncmp(n, "radius", 6) ? get_number(val) : o->prim.sphere.radius;
		o->prim.sphere.r2 = o->prim.sphere.radius * o->prim.sphere.radius;
	}
	else if (o->type == cylinder)
	{
		o->prim.cylinder.origin = !ft_strncmp(n, "origin", 6) ? get_float3(val) : o->prim.cylinder.origin;
		o->prim.cylinder.normal = !ft_strncmp(n, "normal", 6) ? get_float3(val) : o->prim.cylinder.normal;
		o->prim.cylinder.radius = !ft_strncmp(n, "radius", 6) ? get_number(val) : o->prim.cylinder.radius;
		o->prim.cylinder.r2 = o->prim.cylinder.radius * o->prim.cylinder.radius;
		o->prim.cylinder.height = !ft_strncmp(n, "height", 6) ? get_number(val) : o->prim.cylinder.height;
	}
}

void				get_primitives_details3(t_object *o, char *n, struct _json_value *val)
{
	if (o->type == torus)
	{
		o->prim.torus.origin = !ft_strncmp(n, "origin", 6) ? get_float3(val) : o->prim.torus.origin;
		o->prim.torus.normal = !ft_strncmp(n, "normal", 6) ? get_float3(val) : o->prim.torus.normal;
		o->prim.torus.big_radius2 = !ft_strncmp(n, "big_radius2", 11) ? get_number(val) : o->prim.torus.big_radius2;
		o->prim.torus.small_radius2 = !ft_strncmp(n, "small_radius2", 13) ? get_number(val) : o->prim.torus.small_radius2;
	}
	if (o->type == mobius)
	{
		o->prim.mobius.radius = !ft_strncmp(n, "radius", 6) ? get_number(val) : o->prim.mobius.radius;
		o->prim.mobius.half_width = !ft_strncmp(n, "half_width", 10) ? get_number(val) : o->prim.mobius.half_width;
	}
}


void			get_objects_details(t_object *o, char *n, struct _json_value *val)
{
	o->type = !ft_strcmp(n, "type") ? get_type(val) : o->type;
	o->material = !ft_strcmp(n, "material") ? get_float4(val) : o->material;
	o->color = !ft_strcmp(n, "color") ? get_float3(val) : o->color;
	if (o->type == plane || o->type == sphere || o->type == cylinder)
		get_primitives_details(o, n, val);
	else if (o->type == cone || o->type == disk)
		get_primitives_details2(o, n, val);
	else if  (o->type == torus || o->type == mobius)
		get_primitives_details3(o, n, val);
	o->texture = !ft_strcmp(n, "texture") ? get_uchar4(val) : o->texture;
}
