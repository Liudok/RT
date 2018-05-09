
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

void				parse_objects(json_value *value, t_scene *s)
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
		get_object_info(value->u.array.values[i], &s->objs[i]);
	}
}

void 				print_cam(t_camera *o);
static void			parse_value(json_value *value, t_scene *s)
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
			parse_objects(value->u.object.values[i].value, s);
		else if (!ft_strcmp(value->u.object.values[i].name, "camera"))
			parse_camera(value->u.object.values[i].value, s);
	}
//	printf("AMOUNT OF OBJECTS ON THIS SCENE: %i\n", s->objnum);
//	print_cam(&s->camera);
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
