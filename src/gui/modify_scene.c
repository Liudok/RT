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



void        modify_scene(t_rt *rt, int i)
{
	static float3 origin = {{-2, 5, 10}};

    remalloc_objs(rt);
    if (i == 4)
        add_new_sphere(rt, origin);
    if (i == 5)
        add_new_plane(rt, origin);
	if (i == 6)
		add_new_cylinder(rt, origin);
	if (i == 7)
		add_new_cone(rt, origin);
    if (i == 10)
        add_new_triangle(rt, origin);
    reinit_opencl(rt);
	origin.x += 2;
    rt->buttons[3].pressed = 0;
}