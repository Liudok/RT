
#include <OpenCL/opencl.h>
#include "../../include/parser.h"

static void			get_object_info(json_value *value, t_object *o)
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

t_object			second_sphere(t_object *o)
{
	t_object tmp;

	tmp.type = second;
	tmp.prim = o->prim;
	tmp.prim.sphere.origin.s0 += o->prim.sphere.r2 / 2.f;
	tmp.color = o->color;
	tmp.texture = o->texture;
	tmp.material = o->material;
	tmp.ior = 1;
	tmp.roughness = o->roughness;
	return (tmp);
}

void				parse_objects(json_value *value, t_scene *s, t_rt *rt)
{
	int				i;

	s->objnum = value->u.object.length;
	s->objs = (t_object*)malloc(sizeof(t_object) * s->objnum);
	ft_bzero(s->objs, sizeof(s->objs) * s->objnum);
	i = -1;
	while (++i < (int)(s->objnum))
	{
		if (value->u.array.values[i]->type != json_object)
			ft_error("Not valid json object.");
		s->objs[i].type = not_valid;
		s->objs[i].material = 0;
		s->objs[i].color = (float3){{0.0, 0.9, 0.8}};
		s->objs[i].roughness = 0;
		s->objs[i].ior = 1;
		s->objs[i].texture = (uchar4){{0, 0, 0, 0}};
		s->objs[i].prim.sphere.origin = (float3){{0.0, 0.0, 5}};
		get_object_info(value->u.array.values[i], &s->objs[i]);
		if (s->objs[i].type == bool_substraction || s->objs[i].type == bool_intersection)
		{
			++i;
			remalloc_objs(rt);
			s->objs[i] = second_sphere(&s->objs[i - 1]);
		}
	}
}

static void			parse_value(json_value *value, t_scene *s, t_rt *rt)
{
	int				length;
	int				i;

	if (value == NULL)
		return ;
	length = value->u.object.length;
	i = -1;
	while (++i < length)
	{
		if (!ft_strcmp(value->u.object.values[i].name, "objects"))
			parse_objects(value->u.object.values[i].value, s, rt);
		else if (!ft_strcmp(value->u.object.values[i].name, "camera"))
			parse_camera(value->u.object.values[i].value, s);
	}
}

static void			check_json_value(json_value *value, t_scene *s, t_rt *rt)
{
	if (value == NULL)
		return ;
	if (value->type == json_none)
		ft_putendl("none");
	else if (value->type == json_object)
		parse_value(value, s, rt);
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

 void				start_parsing(char *file_str, t_scene *s, int size, t_rt *rt)
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
	 check_json_value(value, s, rt);
	 json_value_free(value);
	 free(file_str);
 }
