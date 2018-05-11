/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_prim2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 11:29:50 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/08 11:29:53 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/panels.h"

void				add_new_disk(t_rt *rt, float3 origin)
{
	rt->scene.objs[rt->scene.objnum - 1].type = disk;
	rt->scene.objs[rt->scene.objnum - 1].color = (float3){{0.3, 0.8, 0.6}};
	rt->scene.objs[rt->scene.objnum - 1].material = diffuse;
	rt->scene.objs[rt->scene.objnum - 1].roughness = 0;
	rt->scene.objs[rt->scene.objnum - 1].ior = 1;
	rt->scene.objs[rt->scene.objnum - 1].texture = (uchar4){{0, 0, 0, 0}};
	rt->scene.objs[rt->scene.objnum - 1].prim = new_disk(origin,
														(float3){{0, 1, 0}}, 3);
}

t_primitive			new_torus(float3 origin, float3 normal,
								float small_radius2, float big_radius2)
{
	t_primitive		prim;

	prim.torus.origin = origin;
	prim.torus.origin.x = prim.torus.origin.x * (-1);
	prim.torus.normal = normal;
	prim.torus.big_radius2 = big_radius2;
	prim.torus.small_radius2 = small_radius2;
	return (prim);
}

void				add_new_torus(t_rt *rt, float3 origin)
{
	rt->scene.objs[rt->scene.objnum - 1].type = torus;
	rt->scene.objs[rt->scene.objnum - 1].color = (float3){{0.9, 0.8, 0.2}};
	rt->scene.objs[rt->scene.objnum - 1].material = diffuse;
	rt->scene.objs[rt->scene.objnum - 1].roughness = 0;
	rt->scene.objs[rt->scene.objnum - 1].ior = 1;
	rt->scene.objs[rt->scene.objnum - 1].texture = (uchar4){{0, 0, 0, 0}};
	rt->scene.objs[rt->scene.objnum - 1].prim = new_torus(origin,
										(float3){{0, 1, 0}}, 1, 2);
}

t_primitive			new_cube(float3 origin, float3 min,
								float3 max, int pipes_number)
{
	t_primitive		prim;

	prim.cube.min = min;
	prim.cube.max = max;
	prim.cube.max.x += origin.x + 1;
	prim.cube.min.x += origin.x + 1;
	prim.cube.pipes_number = pipes_number;
	return (prim);
}

void				add_new_cube(t_rt *rt, float3 origin)
{
	rt->scene.objs[rt->scene.objnum - 1].type = cube;
	rt->scene.objs[rt->scene.objnum - 1].color = (float3){{0.9, 0.8, 0.2}};
	rt->scene.objs[rt->scene.objnum - 1].material = diffuse;
	rt->scene.objs[rt->scene.objnum - 1].roughness = 0;
	rt->scene.objs[rt->scene.objnum - 1].ior = 1;
	rt->scene.objs[rt->scene.objnum - 1].texture = (uchar4){{0, 0, 0, 0}};
	rt->scene.objs[rt->scene.objnum - 1].prim = new_cube(origin,
				(float3){{-1, 1, 4}}, (float3){{-3, 3, 6}}, 0);
}
