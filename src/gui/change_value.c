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

cl_float		my_atof(const char *val, float min, float max)
{
	cl_float ret;

	ret = (cl_float)atof(val);
	if (ret < min)
		ret = min;
	else if (ret > max)
		ret = max;
	return (ret);
}

cl_uchar		my_uchar(const char *val, float min, float max)
{
	cl_uchar	ret;
	int			int_ret;

	int_ret = ft_atoi(val);
	if (int_ret < min)
		int_ret = min;
	else if (int_ret > max)
		int_ret = max;
	ret = (cl_uchar)int_ret;
	return (ret);
}

void		change_appearance(t_rt* rt, int i, int btn, const char *val)
{
	rt->scene.objs[i].color.s0 = (btn == 10) ?
								 my_atof(val, 0, 1) : rt->scene.objs[i].color.s0;
	rt->scene.objs[i].color.s1 = (btn == 11) ?
								 my_atof(val, 0, 1) : rt->scene.objs[i].color.s1;
	rt->scene.objs[i].color.s2 = (btn == 12) ?
								 my_atof(val, 0, 1) : rt->scene.objs[i].color.s2;
	rt->scene.objs[i].material = (btn == 13) ?
								 my_uchar(val, 0, 4) : rt->scene.objs[i].material;
	rt->scene.objs[i].roughness = (btn == 14) ?
								  my_atof(val, 0, 1) : rt->scene.objs[i].roughness;
	rt->scene.objs[i].ior = (btn == 15) ?
							my_atof(val, 1, 2.6) : rt->scene.objs[i].ior;
	rt->scene.objs[i].texture.s0 = (btn == 16) ? my_uchar(val, 0, 255) :
								   rt->scene.objs[i].texture.s0;
	rt->scene.objs[i].texture.s1 = (btn == 17) ? my_uchar(val, 0, 255) :
								   rt->scene.objs[i].texture.s1;
	rt->scene.objs[i].texture.s2 = (btn == 18) ? my_uchar(val, 0, 255) :
								   rt->scene.objs[i].texture.s2;
	rt->scene.objs[i].texture.s3 = (btn == 19) ? my_uchar(val, 0, 255) :
								   rt->scene.objs[i].texture.s2;
}

void		change_origin_and_normal(t_rt* rt, int i, int btn, const char *val)
{
	rt->scene.objs[i].prim.plane.origin.s0 = (btn == 20) ?
		my_atof(val, MINF, MAXF) : rt->scene.objs[i].prim.plane.origin.s0;
	rt->scene.objs[i].prim.plane.origin.s1 = (btn == 21) ?
        my_atof(val, MINF, MAXF) : rt->scene.objs[i].prim.plane.origin.s1;
	rt->scene.objs[i].prim.plane.origin.s2 = (btn == 22) ?
        my_atof(val, MINF, MAXF) : rt->scene.objs[i].prim.plane.origin.s2;
	rt->scene.objs[i].prim.plane.normal.s0 = (btn == 23) ?
        my_atof(val, MINF, MAXF) : rt->scene.objs[i].prim.plane.normal.s0;
	if (rt->scene.objs[i].type == sphere)
	{
		rt->scene.objs[i].prim.sphere.radius = (btn == 23) ?
          my_atof(val, MINF, MAXF) : rt->scene.objs[i].prim.sphere.radius;
		rt->scene.objs[i].prim.sphere.r2 = rt->scene.objs[i].prim.sphere.radius *
                rt->scene.objs[i].prim.sphere.radius;
	}
	else
	{
		rt->scene.objs[i].prim.plane.normal.s1 = (btn == 24) ?
          my_atof(val, MINF, MAXF) : rt->scene.objs[i].prim.plane.normal.s1;
		rt->scene.objs[i].prim.plane.normal.s2 = (btn == 25) ?
          my_atof(val, MINF, MAXF) : rt->scene.objs[i].prim.plane.normal.s2;
	}
}

void		change_triangle_and_cone(t_rt* rt, int i, int btn, const char *val)
{
    if (rt->scene.objs[i].type == triangle)
    {
        rt->scene.objs[i].prim.triangle.vertex2.s0 = (btn == 26) ?
            my_atof(val, MINF, MAXF) : rt->scene.objs[i].prim.triangle.vertex2.s0;
        rt->scene.objs[i].prim.triangle.vertex2.s1 = (btn == 27) ?
            my_atof(val, MINF, MAXF) : rt->scene.objs[i].prim.triangle.vertex2.s1;
        rt->scene.objs[i].prim.triangle.vertex2.s2 = (btn == 28) ?
            my_atof(val, MINF, MAXF) : rt->scene.objs[i].prim.triangle.vertex2.s2;
    }
    else if (rt->scene.objs[i].type == cone)
    {
        rt->scene.objs[i].prim.cone.half_tangent = (btn == 26) ?
            my_atof(val, MINF, MAXF) : rt->scene.objs[i].prim.cone.half_tangent;
        rt->scene.objs[i].prim.cone.m1 = (btn == 27) ?
            my_atof(val, MINF, MAXF) : rt->scene.objs[i].prim.cone.m1;
        rt->scene.objs[i].prim.cone.m2 = (btn == 28) ?
            my_atof(val, MINF, MAXF) : rt->scene.objs[i].prim.cone.m2;
    }
}

void		change_value(t_rt* rt, int i, int btn)
{
	const char *val;

	val = tinyfd_inputBox("", "Put value:", "0");
	if (val != NULL)
	{
		change_appearance(rt, i, btn, val);
		change_origin_and_normal(rt, i, btn, val);
		if (rt->scene.objs[i].type == triangle || rt->scene.objs[i].type == cone)
            change_triangle_and_cone(rt, i, btn, val);
		else if (rt->scene.objs[i].type == cylinder || rt->scene.objs[i].type == torus)
		{
			rt->scene.objs[i].prim.cylinder.radius = (btn == 26) ?
				my_atof(val, MINF, MAXF) : rt->scene.objs[i].prim.cylinder.radius;
			rt->scene.objs[i].prim.cylinder.r2 =
				rt->scene.objs[i].prim.cylinder.radius * rt->scene.objs[i].prim.cylinder.radius;
			rt->scene.objs[i].prim.cylinder.height = (btn == 27) ?
				my_atof(val, MINF, MAXF) : rt->scene.objs[i].prim.cylinder.height;
		}
		else if (rt->scene.objs[i].type == disk)
		{
			rt->scene.objs[i].prim.disk.radius2 = (btn == 26) ?
				my_atof(val, MINF, MAXF) : rt->scene.objs[i].prim.disk.radius2;
		}
	}
}