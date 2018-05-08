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
//void		change_origin_
void		change_value(t_rt* rt, int i, int btn)
{
	const char *val;

	val = tinyfd_inputBox("", "put value", "0");
	if (val != NULL)
	{
		rt->scene.objs[i].color.s0 = (btn == 10) ? (cl_float)atof(val) : rt->scene.objs[i].color.s0;
		rt->scene.objs[i].color.s1 = (btn == 11) ? (cl_float)atof(val) : rt->scene.objs[i].color.s1;
		rt->scene.objs[i].color.s2 = (btn == 12) ? (cl_float)atof(val) : rt->scene.objs[i].color.s2;
		rt->scene.objs[i].material = (btn == 13) ? (cl_uchar)ft_atoi(val) : rt->scene.objs[i].material;
		rt->scene.objs[i].roughness = (btn == 14) ? (cl_float)atof(val) : rt->scene.objs[i].roughness;
		rt->scene.objs[i].ior = (btn == 15) ? (cl_float)atof(val) : rt->scene.objs[i].ior;
		rt->scene.objs[i].texture.s0 = (btn == 16) ? (cl_uchar)ft_atoi(val) : rt->scene.objs[i].texture.s0;
		rt->scene.objs[i].texture.s1 = (btn == 17) ? (cl_uchar)ft_atoi(val) : rt->scene.objs[i].texture.s1;
		rt->scene.objs[i].texture.s2 = (btn == 18) ? (cl_uchar)ft_atoi(val) : rt->scene.objs[i].texture.s2;
		rt->scene.objs[i].texture.s3 = (btn == 19) ? (cl_uchar)ft_atoi(val) : rt->scene.objs[i].texture.s2;
		rt->scene.objs[i].prim.plane.origin.s0 = (btn == 20) ? (cl_float)atof(val) : rt->scene.objs[i].prim.plane.origin.s0;
		rt->scene.objs[i].prim.plane.origin.s1 = (btn == 21) ? (cl_float)atof(val) : rt->scene.objs[i].prim.plane.origin.s1;
		rt->scene.objs[i].prim.plane.origin.s2 = (btn == 22) ? (cl_float)atof(val) : rt->scene.objs[i].prim.plane.origin.s2;
		rt->scene.objs[i].prim.plane.normal.s0 = (btn == 23) ? (cl_float)atof(val) : rt->scene.objs[i].prim.plane.normal.s0;
		if (rt->scene.objs[i].type == sphere)
		{
			rt->scene.objs[i].prim.sphere.radius = (btn == 23) ? (cl_float)atof(val) : rt->scene.objs[i].prim.sphere.radius;
			rt->scene.objs[i].prim.sphere.r2 = rt->scene.objs[i].prim.sphere.radius * rt->scene.objs[i].prim.sphere.radius;
		}
		else
		{
			rt->scene.objs[i].prim.plane.normal.s1 = (btn == 24) ? (cl_float)atof(val) : rt->scene.objs[i].prim.plane.normal.s1;
			rt->scene.objs[i].prim.plane.normal.s2 = (btn == 25) ? (cl_float)atof(val) : rt->scene.objs[i].prim.plane.normal.s2;
		}
		if (rt->scene.objs[i].type == triangle)
		{
			rt->scene.objs[i].prim.triangle.vertex2.s0 = (btn == 26) ? (cl_float)atof(val) : rt->scene.objs[i].prim.triangle.vertex2.s0;
			rt->scene.objs[i].prim.triangle.vertex2.s1 = (btn == 27) ? (cl_float)atof(val) : rt->scene.objs[i].prim.triangle.vertex2.s1;
			rt->scene.objs[i].prim.triangle.vertex2.s2 = (btn == 28) ? (cl_float)atof(val) : rt->scene.objs[i].prim.triangle.vertex2.s2;
		}
		else if (rt->scene.objs[i].type == cone)
		{
			rt->scene.objs[i].prim.cone.half_tangent = (btn == 26) ? (cl_float)atof(val) : rt->scene.objs[i].prim.cone.half_tangent;
			rt->scene.objs[i].prim.cone.m1 = (btn == 27) ? (cl_float)atof(val) : rt->scene.objs[i].prim.cone.m1;
			rt->scene.objs[i].prim.cone.m2 = (btn == 28) ? (cl_float)atof(val) : rt->scene.objs[i].prim.cone.m2;
		}
		else if (rt->scene.objs[i].type == cylinder)
		{
			rt->scene.objs[i].prim.cylinder.radius = (btn == 26) ? (cl_float)atof(val) : rt->scene.objs[i].prim.cylinder.radius;
			rt->scene.objs[i].prim.cylinder.r2 = rt->scene.objs[i].prim.cylinder.radius * rt->scene.objs[i].prim.cylinder.radius;
			rt->scene.objs[i].prim.cylinder.height = (btn == 27) ? (cl_float)atof(val) : rt->scene.objs[i].prim.cylinder.height;
		}
		else if (rt->scene.objs[i].type == disk)
		{
			rt->scene.objs[i].prim.disk.radius2 = (btn == 26) ? (cl_float)atof(val) : rt->scene.objs[i].prim.disk.radius2;
		}
	}
}