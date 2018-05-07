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
//void		change_specific
void		change_value(t_rt* rt, int i, int btn)
{
	const char *val;

	val = tinyfd_inputBox("", "put value", "0");
	if (val != NULL)
	{
		printf("btn = %i\n", btn);
		rt->scene.objs[i].color.s0 = (btn == 8) ? (cl_float)atof(val) : rt->scene.objs[i].color.s0;
		rt->scene.objs[i].color.s1 = (btn == 9) ? (cl_float)atof(val) : rt->scene.objs[i].color.s1;
		rt->scene.objs[i].color.s2 = (btn == 10) ? (cl_float)atof(val) : rt->scene.objs[i].color.s2;
		rt->scene.objs[i].material.s0 = (btn == 11) ? (cl_float)atof(val) : rt->scene.objs[i].material.s0;
		rt->scene.objs[i].material.s1 = (btn == 12) ? (cl_float)atof(val) : rt->scene.objs[i].material.s1;
		rt->scene.objs[i].material.s2 = (btn == 13) ? (cl_float)atof(val) : rt->scene.objs[i].material.s2;
		rt->scene.objs[i].material.s2 = (btn == 14) ? (cl_float)atof(val) : rt->scene.objs[i].material.s3;
		rt->scene.objs[i].texture.s0 = (btn == 15) ? (cl_uchar)ft_atoi(val) : rt->scene.objs[i].texture.s0;
		rt->scene.objs[i].texture.s1 = (btn == 16) ? (cl_uchar)ft_atoi(val) : rt->scene.objs[i].texture.s1;
		rt->scene.objs[i].texture.s2 = (btn == 17) ? (cl_uchar)ft_atoi(val) : rt->scene.objs[i].texture.s2;
		rt->scene.objs[i].prim.plane.origin.s0 = (btn == 18) ? (cl_float)atof(val) : rt->scene.objs[i].prim.plane.origin.s0;
		rt->scene.objs[i].prim.plane.origin.s1 = (btn == 19) ? (cl_float)atof(val) : rt->scene.objs[i].prim.plane.origin.s1;
		rt->scene.objs[i].prim.plane.origin.s2 = (btn == 20) ? (cl_float)atof(val) : rt->scene.objs[i].prim.plane.origin.s2;
		rt->scene.objs[i].prim.plane.normal.s0 = (btn == 21) ? (cl_float)atof(val) : rt->scene.objs[i].prim.plane.normal.s0;
		if (rt->scene.objs[i].type == sphere)
		{
			rt->scene.objs[i].prim.sphere.radius = (btn == 21) ? (cl_float)atof(val) : rt->scene.objs[i].prim.sphere.radius;
			rt->scene.objs[i].prim.sphere.r2 = rt->scene.objs[i].prim.sphere.radius * rt->scene.objs[i].prim.sphere.radius;
		}
		else
		{
			rt->scene.objs[i].prim.plane.normal.s1 = (btn == 22) ? (cl_float)atof(val) : rt->scene.objs[i].prim.plane.normal.s1;
			rt->scene.objs[i].prim.plane.normal.s2 = (btn == 23) ? (cl_float)atof(val) : rt->scene.objs[i].prim.plane.normal.s2;
		}
	}
}