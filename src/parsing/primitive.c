/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 19:00:50 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/07 13:39:46 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/parser.h"

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

void		get_primitives_details6(t_object *o, char *n, struct _json_value *val)
{
	if (o->type == bool_substraction || o->type == bool_intersection)
	{
		o->prim.sphere.origin = !ft_strncmp(n, "origin", 6) ? get_float3(val) : o->prim.sphere.origin;
		o->prim.sphere.radius = 2;
		o->prim.sphere.r2 = o->prim.sphere.radius * o->prim.sphere.radius;

	}
}


void			get_objects_details(t_object *o, char *n, struct _json_value *val)
{
	o->type = !ft_strcmp(n, "type") ? get_type(val) : o->type;
	o->material = !ft_strcmp(n, "material") ? get_material(val) : o->material;
	o->roughness = !ft_strcmp(n, "roughness") ? get_number(val) : o->roughness;
	o->ior = !ft_strcmp(n, "ior") ? get_number(val) : o->ior;
	o->color = !ft_strcmp(n, "color") ? get_float3(val) : o->color;
	if (o->type == plane || o->type == sphere || o->type == cylinder)
		get_primitives_details(o, n, val);
	else if (o->type == cone || o->type == disk)
		get_primitives_details2(o, n, val);
	else if  (o->type == torus || o->type == mobius)
		get_primitives_details3(o, n, val);
	else if  (o->type == triangle || o->type == cube)
		get_primitives_details4(o, n, val);
	else if  (o->type == bool_substraction || o->type == bool_intersection)
		get_primitives_details6(o, n, val);
	else if  (o->type == parabaloid || o->type == julia)
		get_primitives_details5(o, n, val);
	o->texture = !ft_strcmp(n, "texture") ? get_uchar4(val) : o->texture;
}
