/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 13:49:07 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/12 13:49:08 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/opencl.h>
#include "../../include/parser.h"

void				parse_objects(json_value *value, t_scene *s)
{
	int				i;
	int				j;

	s->objnum = value->u.object.length;
	s->objs = (t_object*)malloc(sizeof(t_object) * s->objnum);
	ft_bzero(s->objs, sizeof(s->objs) * s->objnum);
	i = -1;
	j = 0;
	while (++i < (int)(s->objnum))
	{
		put_default(value, s, i, j);
		if (s->objs[i].type == bool_substraction ||
				s->objs[i].type == bool_intersection)
		{
			++i;
			remalloc_objscene(s);
			s->objs[i] = second_sphere(&s->objs[i - 1]);
		}
		else if (s->objs[i].type == cube)
		{
			second_cylinder(i, s);
			i += s->objs[i].prim.cube.pipes_number;
		}
		++j;
	}
}

void				parsing_while(json_value *value, t_scene *s,
									void (*validators[])(void *))
{
	int				i;
	int				length;

	i = -1;
	length = value->u.object.length;
	while (++i < length)
	{
		if (!ft_strcmp(value->u.object.values[i].name, "objects"))
			parse_objects(value->u.object.values[i].value, s);
		else if (!ft_strcmp(value->u.object.values[i].name, "camera"))
			parse_camera(value->u.object.values[i].value, s);
	}
	i = -1;
	while (++i < (int)s->objnum)
	{
		validation(&s->objs[i]);
		validation_fix(&s->objs[i]);
		validators[s->objs[i].type](&s->objs[i].prim);
	}
}

static void			parse_value(json_value *value, t_scene *s)
{
	static void (*validators[])(void *) = {
			(void (*)(void *))validation_sphere,
			(void (*)(void *))validation_plane,
			(void (*)(void *))validation_cylinder,
			(void (*)(void *))validation_cone,
			(void (*)(void *))validation_disk,
			(void (*)(void *))validation_torus,
			(void (*)(void *))validation_triangle,
			(void (*)(void *))validation_mobius,
			(void (*)(void *))validation_sphere,
			(void (*)(void *))validation_sphere,
			(void (*)(void *))validation_cube,
			(void (*)(void *))validation_parabaloid,
			(void (*)(void *))validation_julia,
			(void (*)(void *))validation_sphere
	};

	if (value == NULL)
		return ;
	parsing_while(value, s, validators);
}

static void			check_json_value(json_value *value, t_scene *s)
{
	if (value == NULL)
		return ;
	if (value->type == json_none)
		ft_putendl("none");
	else if (value->type == json_object)
		parse_value(value, s);
	else if (value->type == json_array)
		ft_error("Unexpected array.");
	else if (value->type == json_integer)
		ft_error("Unexpected integer.");
	else if (value->type == json_double)
		ft_error("Unexpected double.");
	else if (value->type == json_string)
		ft_error("Unexpected string.");
	else if (value->type == json_boolean)
		ft_error("Unexpected boolean.");
}

void				start_parsing(char *file_str, t_scene *s, int size)
{
	json_char		*json;
	json_value		*value;

	json = (json_char*)file_str;
	value = json_parse(json, size);
	if (value == NULL)
	{
		free(file_str);
		ft_error("Unable to parse json data");
	}
	check_json_value(value, s);
	json_value_free(value);
	free(file_str);
}
