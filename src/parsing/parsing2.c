/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 13:49:13 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/12 13:49:16 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/opencl.h>
#include "../../include/parser.h"

void				get_object_info(json_value *value, t_object *o)
{
	unsigned int	i;
	char			*n;

	i = 0;
	while (i < value->u.object.length)
	{
		n = value->u.object.values[i].name;
		get_objects_details(o, n, value->u.object.values[i].value);
		if (o->type == not_valid)
			ft_error("Not valid type.");
		if (!validation(o))
			g_error_flag = 1;
		i++;
	}
}

void				put_default(json_value *value, t_scene *s, int i, int j)
{
	if (value->u.array.values[j]->type != json_object)
		ft_error("Not valid json object.");
	s->objs[i].type = not_valid;
	s->objs[i].material = 0;
	s->objs[i].color = (cl_float3){{0.0, 0.9, 0.8}};
	s->objs[i].roughness = 0;
	s->objs[i].ior = 1;
	s->objs[i].texture = (cl_uchar4){{0, 0, 0, 0}};
	s->objs[i].prim.sphere.origin = (cl_float3){{0.0, 0.0, 5}};
	get_object_info(value->u.array.values[j], &s->objs[i]);
}

void				remalloc_objscene(t_scene *scene)
{
	t_object		*tmp_objs;
	unsigned int	i;

	tmp_objs = scene->objs;
	scene->objnum++;
	scene->objs = (t_object*)malloc(sizeof(t_object) * scene->objnum);
	ft_bzero(scene->objs, sizeof(scene->objs) * scene->objnum);
	i = 0;
	while (i < scene->objnum - 1)
	{
		scene->objs[i] = tmp_objs[i];
		i++;
	}
	free(tmp_objs);
}

t_object			second_sphere(t_object *o)
{
	t_object		tmp;

	tmp.type = second;
	tmp.prim = o->prim;
	tmp.prim.sphere.origin.s0 += o->prim.sphere.r2 / 2.f;
	tmp.color = o->color;
	tmp.texture = o->texture;
	tmp.material = o->material;
	if (o->type == bool_substraction)
	{
		tmp.texture.s0 = 255;
		tmp.material = 3;
	}
	tmp.ior = o->ior;
	tmp.roughness = o->roughness;
	return (tmp);
}

void				second_cylinder(int j, t_scene *s)
{
	t_object		tmp;
	cl_float3		normal;
	int				i;
	t_object		*o;

	i = -1;
	o = &s->objs[j];
	while (++i < o->prim.cube.pipes_number)
	{
		remalloc_objscene(s);
		o = &s->objs[j];
		normal = (cl_float3){{0, 0, 0}};
		normal.s[i % 3] = 1;
		tmp.type = cylinder;
		tmp.prim = new_cylinder(vadd(o->prim.cube.min,
			vmul(vsub(o->prim.cube.max, o->prim.cube.min), i /
			(float)o->prim.cube.pipes_number / 2 + 0.5f)), normal, 0.2f, 2);
		tmp.prim.cylinder.origin.s[i % 3] = o->prim.cube.max.s[i % 3];
		tmp.color = o->color;
		tmp.texture = o->texture;
		tmp.material = o->material;
		tmp.ior = o->ior;
		tmp.roughness = o->roughness;
		o[i + 1] = tmp;
	}
}
