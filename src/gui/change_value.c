/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 12:35:40 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/07 12:35:42 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/panels.h"

cl_float	my_atof(const char *val, float min, float max)
{
	cl_float ret;

	ret = (cl_float)atof(val);
	if (ret < min)
		ret = min;
	else if (ret > max)
		ret = max;
	return (ret);
}

void		change_appearance(t_object *o, int btn, const char *val)
{
	o->color.s0 = (btn == 10) ? my_atof(val, 0, 1) : o->color.s0;
	o->color.s1 = (btn == 11) ? my_atof(val, 0, 1) : o->color.s1;
	o->color.s2 = (btn == 12) ? my_atof(val, 0, 1) : o->color.s2;
	o->material = (btn == 13) ? my_atof(val, 0, 4) : o->material;
	o->roughness = (btn == 14) ? my_atof(val, 0, 1) : o->roughness;
	o->ior = (btn == 15) ? my_atof(val, 1, 2.6) : o->ior;
	o->texture.s0 = (btn == 16) ? my_atof(val, 0, 255) : o->texture.s0;
	o->texture.s1 = (btn == 17) ? my_atof(val, 0, 255) : o->texture.s1;
	o->texture.s2 = (btn == 18) ? my_atof(val, 0, 255) : o->texture.s2;
	o->texture.s3 = (btn == 19) ? my_atof(val, 0, 255) : o->texture.s2;
}

void		change_origin_and_normal(t_object *o, int btn, const char *val)
{
	if (btn == 20)
		o->prim.plane.origin.s0 = my_atof(val, MINF, MAXF);
	if (btn == 21)
		o->prim.plane.origin.s1 = my_atof(val, MINF, MAXF);
	if (btn == 22)
		o->prim.plane.origin.s2 = my_atof(val, MINF, MAXF);
	if (btn == 23)
		o->prim.plane.normal.s0 = my_atof(val, MINF, MAXF);
	if (o->type == sphere && btn == 23)
		o->prim.sphere.radius = my_atof(val, MINF, MAXF);
	else if (btn == 24)
		o->prim.plane.normal.s1 = my_atof(val, MINF, MAXF);
	else if (btn == 25)
		o->prim.plane.normal.s2 = my_atof(val, MINF, MAXF);
	o->prim.sphere.r2 = o->prim.sphere.radius * o->prim.sphere.radius;
}

void		change_triangle_and_cone(t_object *o, int btn, const char *val)
{
	if (o->type == triangle)
	{
		o->prim.triangle.vertex2.s0 = (btn == 26) ?
		my_atof(val, MINF, MAXF) : o->prim.triangle.vertex2.s0;
		o->prim.triangle.vertex2.s1 = (btn == 27) ?
		my_atof(val, MINF, MAXF) : o->prim.triangle.vertex2.s1;
		o->prim.triangle.vertex2.s2 = (btn == 28) ?
		my_atof(val, MINF, MAXF) : o->prim.triangle.vertex2.s2;
	}
	else if (o->type == cone)
	{
		o->prim.cone.half_tangent = (btn == 26) ?
		my_atof(val, MINF, MAXF) : o->prim.cone.half_tangent;
		o->prim.cone.m1 = (btn == 27) ?
		my_atof(val, MINF, MAXF) : o->prim.cone.m1;
		o->prim.cone.m2 = (btn == 28) ?
		my_atof(val, MINF, MAXF) : o->prim.cone.m2;
	}
}

void		change_value(t_object *o, const int btn)
{
	const char *val;

	val = tinyfd_inputBox("", "Put value:", "0");
	if (val != NULL)
	{
		change_appearance(o, btn, val);
		change_origin_and_normal(o, btn, val);
		if (o->type == triangle || o->type == cone)
			change_triangle_and_cone(o, btn, val);
		else if (o->type == cylinder && btn == 26)
			o->prim.cylinder.radius = my_atof(val, MINF, MAXF);
		else if (o->type == cylinder && btn == 27)
			o->prim.cylinder.height = my_atof(val, MINF, MAXF);
		else if (o->type == torus && btn == 26)
			o->prim.torus.big_radius2 = my_atof(val, MINF, MAXF);
		else if (o->type == torus && btn == 27)
			o->prim.torus.small_radius2 = my_atof(val, MINF, MAXF);
		else if (o->type == disk && btn == 26)
			o->prim.disk.radius2 = my_atof(val, MINF, MAXF);
		o->prim.cylinder.r2 = o->prim.cylinder.radius * o->prim.cylinder.radius;
	}
}
