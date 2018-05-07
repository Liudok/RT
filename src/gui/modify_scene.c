/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 12:20:59 by lberezyn          #+#    #+#             */
/*   Updated: 2018/04/27 12:21:02 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/panels.h"

void        remalloc_objs(t_rt *rt)
{
    t_object		*tmp_objs;
    unsigned int i;

    tmp_objs = rt->scene.objs;
    rt->scene.objnum++;
    rt->scene.objs = (t_object*)malloc(sizeof(t_object) * rt->scene.objnum);
    ft_bzero(rt->scene.objs, sizeof(rt->scene.objs) * rt->scene.objnum);
    i = 0;
    while (i < rt->scene.objnum - 1)
    {
        rt->scene.objs[i] = tmp_objs[i];
        i++;
    }
    free(tmp_objs);
}

void        add_new_disk(t_rt *rt, float3 origin)
{
	rt->scene.objs[rt->scene.objnum - 1].type = disk;
	rt->scene.objs[rt->scene.objnum - 1].color = (float3){{0.3, 0.8, 0.6}};
	rt->scene.objs[rt->scene.objnum - 1].material = (float4){{0, 0, 0, 0}};
	rt->scene.objs[rt->scene.objnum - 1].texture = (uchar4){{0, 0, 0, 0}};
	rt->scene.objs[rt->scene.objnum - 1].prim = new_disk(origin, (float3){{0, 1, 0}}, 3);
}

t_primitive			new_torus(float3 origin, float3 normal, float small_radius2, float big_radius2)
{
	t_primitive		prim;

	prim.torus.origin = origin;
	prim.torus.origin.x = prim.torus.origin.x * (-1);
	prim.torus.normal = normal;
	prim.torus.big_radius2 = big_radius2;
	prim.torus.small_radius2 = small_radius2;
	return (prim);
}

void        add_new_torus(t_rt *rt, float3 origin)
{
	rt->scene.objs[rt->scene.objnum - 1].type = torus;
	rt->scene.objs[rt->scene.objnum - 1].color = (float3){{0.9, 0.8, 0.2}};
	rt->scene.objs[rt->scene.objnum - 1].material = (float4){{0, 0, 0, 0}};
	rt->scene.objs[rt->scene.objnum - 1].texture = (uchar4){{0, 0, 0, 0}};
	rt->scene.objs[rt->scene.objnum - 1].prim = new_torus(origin, (float3){{0, 1, 0}}, 3, 5);
}

t_primitive			new_cube(float3 origin, float3 min, float3 max, int pipes_number)
{
	t_primitive		prim;

	prim.cube.min = min;
	prim.cube.max = max;
	prim.cube.max.x += origin.x + 1;
	prim.cube.min.x += origin.x + 1;
	prim.cube.pipes_number = pipes_number;
	return (prim);
}

void        add_new_cube(t_rt *rt, float3 origin)
{
	rt->scene.objs[rt->scene.objnum - 1].type = cube;
	rt->scene.objs[rt->scene.objnum - 1].color = (float3){{0.9, 0.8, 0.2}};
	rt->scene.objs[rt->scene.objnum - 1].material = (float4){{0, 0, 0, 0}};
	rt->scene.objs[rt->scene.objnum - 1].texture = (uchar4){{0, 0, 0, 0}};
	rt->scene.objs[rt->scene.objnum - 1].prim = new_cube(origin, (float3){{-1, 1, 4}}, (float3){{-3, 3, 6}}, 0);
}

void        modify_scene(t_rt *rt, int i)
{
	static float3 origin = {{-2, 2, 10}};

    remalloc_objs(rt);
    if (i == 4)
        add_new_sphere(rt, origin);
	else if (i == 5)
        add_new_plane(rt, origin);
	else if (i == 6)
		add_new_cylinder(rt, origin);
	else if (i == 7)
		add_new_cone(rt, origin);
	else if (i == 8)
		add_new_disk(rt, origin);
	else if (i == 9)
		add_new_torus(rt, origin);
	else if (i == 10)
        add_new_triangle(rt, origin);
	else if (i == 11)
		add_new_cube(rt, origin);
    reinit_opencl(rt);
	origin.x += 2;
    rt->buttons[3].pressed = 0;
}