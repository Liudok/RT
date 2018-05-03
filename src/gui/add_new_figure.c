/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_figure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:08:59 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/03 13:09:02 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/panels.h"

void        add_new_cone(t_rt *rt, float3 origin)
{
	rt->scene.objs[rt->scene.objnum - 1].type = cone;
	rt->scene.objs[rt->scene.objnum - 1].color = (float3){{0.2, 0.6, 0.8}};
	rt->scene.objs[rt->scene.objnum - 1].material = (float4){{1, 0, 0, 0}};
	rt->scene.objs[rt->scene.objnum - 1].texture = (uchar4){{0, 0, 0, 0}};
	rt->scene.objs[rt->scene.objnum - 1].prim = new_cone(origin, (float3){{0, -1, 0}}, 0.0, 2.5);
}

void        add_new_cylinder(t_rt *rt, float3 origin)
{
	rt->scene.objs[rt->scene.objnum - 1].type = cylinder;
	rt->scene.objs[rt->scene.objnum - 1].color = (float3){{0.5, 0.3, 0.8}};
	rt->scene.objs[rt->scene.objnum - 1].material = (float4){{0.7, 0, 0, 0}};
	rt->scene.objs[rt->scene.objnum - 1].texture = (uchar4){{0, 0, 0, 0}};
	rt->scene.objs[rt->scene.objnum - 1].prim = new_cylinder(origin, (float3){{0, 1, 0}}, 0.8, 1.5);
}

void        add_new_plane(t_rt *rt, float3 origin)
{
	rt->scene.objs[rt->scene.objnum - 1].type = plane;
	rt->scene.objs[rt->scene.objnum - 1].color = (float3){{0.5, 0.3, 0.8}};
	rt->scene.objs[rt->scene.objnum - 1].material = (float4){{0, 0, 0, 0}};
	rt->scene.objs[rt->scene.objnum - 1].texture = (uchar4){{0, 0, 0, 0}};
	rt->scene.objs[rt->scene.objnum - 1].prim = new_plane(origin, (float3){{1, 0, 0}});
}

void        add_new_sphere(t_rt *rt, float3 origin)
{
	rt->scene.objs[rt->scene.objnum - 1].type = sphere;
	rt->scene.objs[rt->scene.objnum - 1].color = (float3){{0.9, 0.9, 0.1}};
	rt->scene.objs[rt->scene.objnum - 1].material = (float4){{0, 0, 0, 0}};
	rt->scene.objs[rt->scene.objnum - 1].texture = (uchar4){{0, 0, 0, 0}};
	rt->scene.objs[rt->scene.objnum - 1].prim = new_sphere(origin, 1);
}

void        add_new_triangle(t_rt *rt, float3 origin)
{
	rt->scene.objs[rt->scene.objnum - 1].type = triangle;
	rt->scene.objs[rt->scene.objnum - 1].color = (float3){{0.9, 0.9, 0.1}};
	rt->scene.objs[rt->scene.objnum - 1].material = (float4){{0, 0, 0, 0}};
	rt->scene.objs[rt->scene.objnum - 1].texture = (uchar4){{0, 0, 0, 0}};
	rt->scene.objs[rt->scene.objnum - 1].prim.triangle.vertex0 = (float3){{origin.x, 1, 20}};
	rt->scene.objs[rt->scene.objnum - 1].prim.triangle.vertex1 = (float3){{3, origin.x, 15}};
	rt->scene.objs[rt->scene.objnum - 1].prim.triangle.vertex2 = (float3){{0, 5, origin.x}};
}
