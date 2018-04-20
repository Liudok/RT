
# include "../../include/parser.h"

static void			get_object_info(json_value *value, t_object *o)
{
	unsigned int	i;
	char			*n;

	i = 0;
	while (i < value->u.object.length)
	{
		n = value->u.object.values[i].name;
		printf("%s\n",n);
		get_objects_details(o, n, value->u.object.values[i].value);
		if (o->type == not_valid)
			ft_error("Not valid type.");
		i++;
	}
}

void				parse_objects(json_value *value, t_sdl *s)
{
	int				i;

	s->o_amount = value->u.object.length + 1;
	s->objs = (t_object*)ft_memalloc(sizeof(t_object) * s->o_amount);
	ft_bzero(s->objs, sizeof(s->objs) * s->o_amount);
	i = -1;
	while (++i < (s->o_amount - 1))
	{
		if (value->u.array.values[i]->type != json_object)
			ft_error("Not valid json object.");
		s->objs[i].type = not_valid;
		get_object_info(value->u.array.values[i], &s->objs[i]);
//		if (s->object[i].type == O_TRIANGLE)
//			create_triangle_norm(&s->object[i]);
//		else if (s->object[i].type == O_CON)
//			create_conus(&s->object[i]);
//		else if (s->object[i].type == O_ELIPSOID)
//			validate_elipsoid(&s->object[i]);
	}
}

static void			parse_value(json_value *value, t_sdl *s)
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
//		if (!ft_strcmp(value->u.object.values[i].name, "cameras"))
//			process_scene_c(value->u.object.values[i].value, s);
	}
}

static void			check_json_value(json_value *value, t_sdl *s)
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

 void				start_parsing(char *file_str, t_sdl *s, int size)
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
