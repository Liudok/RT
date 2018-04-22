/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 19:00:50 by lberezyn          #+#    #+#             */
/*   Updated: 2018/04/22 11:50:02 by lberezyn         ###   ########.fr       */
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
		o->prim.cylinder.r2 = !ft_strncmp(n, "r2", 2) ? get_number(val) : o->prim.cylinder.r2;
		o->prim.cylinder.height = !ft_strncmp(n, "height", 6) ? get_number(val) : o->prim.cylinder.height;
	}
}

void			get_objects_details(t_object *o, char *n, struct _json_value *val)
{
	o->type = !ft_strcmp(n, "type") ? get_type(val) : o->type;
	o->material = !ft_strcmp(n, "material") ? get_float4(val) : o->material;
	o->color = !ft_strcmp(n, "color") ? get_float3(val) : o->color;
	if (o->type == plane || o->type == sphere || o->type == cylinder || o->type == cone)
		get_primitives_details(o, n, val);
	else if (o->type == cone)
		get_primitives_details2(o, n, val);
	o->texture = !ft_strcmp(n, "texture") ? (uint)get_number(val) : o->texture;
}
