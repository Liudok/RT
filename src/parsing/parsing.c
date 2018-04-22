
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
		i++;
	}
}

void				parse_objects(json_value *value, t_scene *s)
{
	int				i;

	s->objnum = value->u.object.length;
	s->objs = (t_object*)malloc(sizeof(t_object) * s->objnum);
//	ft_bzero(s->objs, sizeof(s->objs) * s->objnum);
	i = -1;
	while (++i < (int)(s->objnum))
	{
		if (value->u.array.values[i]->type != json_object)
			ft_error("Not valid json object.");
		s->objs[i].type = not_valid;
		get_object_info(value->u.array.values[i], &s->objs[i]);
	}
}

void 				print_obj(t_object *o, int n)
{
	int i = 0;
	while (i < n)
	{
		printf("=========== type : %u =============\n", o[i].type);
		printf("material : { %f %f %f %f}\n", o[i].material.s0, o[i].material.s1, o[i].material.s2, o[i].material.s3);
		printf("color : { %f %f %f }\n", o[i].color.s0, o[i].color.s1, o[i].color.s2);
		if (o[i].type == 0)
		{
			printf("prim origin : { %f %f %f }\n", o[i].prim.sphere.origin.s0, o[i].prim.sphere.origin.s1, o[i].prim.sphere.origin.s2);
			printf("radius = %f\n", o[i].prim.sphere.radius);
		}
		i++;
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
		if (!ft_strcmp(value->u.object.values[i].name, "camera"))
			parse_camera(value->u.object.values[i].value, s);
	}
	printf("AMOUNT OF OBJECTS ON THIS SCENE: %i\n", s->objnum);
//	print_obj(s->objs, s->objnum);
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
//	 printf("file_str = %s\n",file_str );
	 if (value == NULL)
	 {
		 free(file_str);
		 ft_error("Unable to parse json data");
	 }
	 check_json_value(value, s);
	 json_value_free(value);
	 free(file_str);
 }
