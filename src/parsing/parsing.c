
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

void        remalloc_objscene(t_scene *scene)
{
	t_object		*tmp_objs;
	unsigned int i;

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
	t_object tmp;

	tmp.type = second;
	tmp.prim = o->prim;
	tmp.prim.sphere.origin.s0 += o->prim.sphere.r2 / 2.f;
	tmp.color = o->color;
	tmp.texture = o->texture;
	tmp.material = o->material;
	tmp.ior = o->ior;
	tmp.roughness = o->roughness;
	return (tmp);
}

void				second_cylinder(int j, t_scene *s)
{
	t_object tmp;
	float3 normal;
	int i;
	t_object *o;

	i = -1;
	o = &s->objs[j];
	while (++i < o->prim.cube.pipes_number)
	{
		remalloc_objscene(s);
		o = &s->objs[j];
		normal = (float3){{0, 0, 0}};
		normal.s[i % 3] = 1;
		tmp.type = cylinder;
		tmp.prim = new_cylinder(vadd(o->prim.cube.min,
	vmul(vsub(o->prim.cube.max, o->prim.cube.min), i / (float)o->prim.cube.pipes_number / (float)2 + 0.5f)), normal, 0.2f, 2);
		tmp.prim.cylinder.origin.s[i % 3] = o->prim.cube.max.s[i % 3];
		tmp.color = o->color;
		tmp.texture = o->texture;
		tmp.material = o->material;
		tmp.ior = o->ior;
		tmp.roughness = o->roughness;
		o[i + 1] = tmp;
	}
}

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
		if (value->u.array.values[j]->type != json_object)
			ft_error("Not valid json object.");
		s->objs[i].type = not_valid;
		s->objs[i].material = 0;
		s->objs[i].color = (float3){{0.0, 0.9, 0.8}};
		s->objs[i].roughness = 0;
		s->objs[i].ior = 1;
		s->objs[i].texture = (uchar4){{0, 0, 0, 0}};
		s->objs[i].prim.sphere.origin = (float3){{0.0, 0.0, 5}};
		get_object_info(value->u.array.values[j], &s->objs[i]);
		if (s->objs[i].type == bool_substraction || s->objs[i].type == bool_intersection)
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

static void			parse_value(json_value *value, t_scene *s)
{
	int				length;
	int				i;
	static void (*validators[])(void *) = {
			(void (*)(void *))validation_sphere,
			(void (*)(void *))validation_plane,
			(void (*)(void *))validation_cylinder,
			(void (*)(void *))validation_cone,
			(void (*)(void *))validation_disk,
			(void (*)(void *))validation_torus,
			(void (*)(void *))validation_triangle,
			(void (*)(void *))validation_sphere,
			(void (*)(void *))validation_sphere,
			(void (*)(void *))validation_sphere,
			(void (*)(void *))validation_sphere,
			(void (*)(void *))validation_sphere,
			(void (*)(void *))validation_sphere,
			(void (*)(void *))validation_sphere,
			(void (*)(void *))validation_sphere,

	};

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
	i = -1;
	while (++i < (int)s->objnum)
	{
		validation(&s->objs[i]);
		validation_fix(&s->objs[i]);
		validators[s->objs[i].type](&s->objs[i].prim);
	}
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
