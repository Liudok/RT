/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 12:20:59 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/11 22:52:42 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/panels.h"

void		add_ambient(t_rt *rt, int i)
{
	rt->scene.camera.ambient.s0 += 0.1;
	rt->scene.camera.ambient.s1 += 0.1;
	rt->scene.camera.ambient.s2 += 0.1;
	add_new_sphere(rt, (cl_float3){{10000, 0, 0}});
	rt->buttons[i].pressed = 0;
}

void		painting_effect(t_rt *rt, int i)
{
	if (rt->painting_flag == 0)
		rt->painting_flag = 1;
	else
		rt->painting_flag = 0;
	add_new_sphere(rt, (cl_float3){{10000, 0, 0}});
	rt->buttons[i].pressed = 0;
}

void		scene_modification(t_rt *rt, int i)
{
	if (i == 12)
		painting_effect(rt, i);
	else if (i == 13)
		add_ambient(rt, i);
	else if (i == 14)
		clean_scene(rt);
}

void		modify_scene(t_rt *rt, int i)
{
	static cl_float3 origin = {{-2, 2, 10}};

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
	else if (i > 11 && i < 15 && rt->buttons[1].pressed)
		scene_modification(rt, i);
	reinit_opencl(rt);
	origin.x += 2;
	rt->buttons[3].pressed = 0;
}

void		clean_scene(t_rt *rt)
{
	rt->scene.objnum = 1;
	free(rt->scene.objs);
	rt->scene.objs = (t_object*)malloc(sizeof(t_object));
	ft_bzero(rt->scene.objs, sizeof(rt->scene.objs) * rt->scene.objnum);
	add_new_disk(rt, (cl_float3){{0, 5, 1}});
	rt->scene.objs[0].material = emission;
	rt->scene.objs[0].color = (cl_float3){{0.9, 0.9, 0.9}};
	rt->scene.objs[0].prim.disk.normal = (cl_float3){{0, 1, -0.1}};
	rt->scene.objs[0].prim.disk.radius2 = 100;
	rt->scene.camera.ambient.s0 = 0;
	rt->scene.camera.ambient.s1 = 0;
	rt->scene.camera.ambient.s2 = 0;
	rt->scene.camera.rotate.x = 0;
	rt->scene.camera.rotate.y = 0;
	rt->buttons[14].pressed = 0;
}
