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

t_primitive	new_sphere(float3 origin, float radius)
{
    t_primitive prim;

    prim.sphere.origin = origin;
    prim.sphere.radius = radius;
    prim.sphere.r2 = radius * radius;
    return (prim);
}

t_primitive	new_plane(float3 origin, float3 normal)
{
    t_primitive prim;

    prim.plane.origin = origin;
    prim.plane.normal = normal;
    return (prim);
}

t_primitive	new_cylinder(float3 origin, float3 normal)
{
	t_primitive prim;

	prim.cylinder.origin = origin;
	prim.cylinder.normal = normal;
	return (prim);
}

void        add_new_cylinder(t_rt *rt)
{
	rt->scene.objs[rt->scene.objnum - 1].type = cylinder;
	rt->scene.objs[rt->scene.objnum - 1].color = (float3){{0.5, 0.3, 0.8}};
	rt->scene.objs[rt->scene.objnum - 1].material = (float4){{0, 0, 0, 0}};
	rt->scene.objs[rt->scene.objnum - 1].texture = (uchar4){{0, 0, 0, 0}};
	rt->scene.objs[rt->scene.objnum - 1].prim = new_cylinder((float3){{(rt->scene.objnum - 1) * 4, 1, 10}}, (float3){{1, 0, 0}});
}

void        add_new_plane(t_rt *rt)
{
    rt->scene.objs[rt->scene.objnum - 1].type = plane;
    rt->scene.objs[rt->scene.objnum - 1].color = (float3){{0.5, 0.3, 0.8}};
    rt->scene.objs[rt->scene.objnum - 1].material = (float4){{0, 0, 0, 0}};
    rt->scene.objs[rt->scene.objnum - 1].texture = (uchar4){{0, 0, 0, 0}};
    rt->scene.objs[rt->scene.objnum - 1].prim = new_plane((float3){{(rt->scene.objnum - 1) * 4, 1, 10}}, (float3){{1, 0, 0}});
}

void        add_new_sphere(t_rt *rt)
{
    rt->scene.objs[rt->scene.objnum - 1].type = sphere;
    rt->scene.objs[rt->scene.objnum - 1].color = (float3){{0.9, 0.9, 0.1}};
    rt->scene.objs[rt->scene.objnum - 1].material = (float4){{0, 0, 0, 0}};
    rt->scene.objs[rt->scene.objnum - 1].texture = (uchar4){{0, 0, 0, 0}};
    rt->scene.objs[rt->scene.objnum - 1].prim = new_sphere((float3){{(rt->scene.objnum - 1) * 4, 1, 10}}, 2);
}

void        add_new_triangle(t_rt *rt)
{
    rt->scene.objs[rt->scene.objnum - 1].type = triangle;
    rt->scene.objs[rt->scene.objnum - 1].color = (float3){{0.9, 0.9, 0.1}};
    rt->scene.objs[rt->scene.objnum - 1].material = (float4){{0, 0, 0, 0}};
    rt->scene.objs[rt->scene.objnum - 1].texture = (uchar4){{0, 0, 0, 0}};
    rt->scene.objs[rt->scene.objnum - 1].prim.triangle.vertex0 = (float3){{rt->scene.objnum - 1, 1, 20}};
    rt->scene.objs[rt->scene.objnum - 1].prim.triangle.vertex1 = (float3){{3, rt->scene.objnum - 1, 15}};
    rt->scene.objs[rt->scene.objnum - 1].prim.triangle.vertex2 = (float3){{0, 5, rt->scene.objnum - 1}};
}

void        modify_scene(t_rt *rt, int i)
{
    remalloc_objs(rt);
    if (i == 4)
        add_new_sphere(rt);
    if (i == 5)
        add_new_plane(rt);
	if (i == 6)
		add_new_cylinder(rt);
    if (i == 10)
        add_new_triangle(rt);
    reinit_opencl(rt);
    rt->buttons[3].pressed = 0;
}