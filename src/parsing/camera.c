
#include <OpenCL/opencl.h>
# include "../../include/parser.h"

void			get_camera_details(t_camera *o, char *n, struct _json_value *val)
{
	o->origin = !ft_strncmp(n, "origin", 6) ? get_float3(val) : o->origin;
	o->dir = !ft_strncmp(n, "dir", 3) ? get_float3(val) : o->dir;
	o->cx = !ft_strncmp(n, "cx", 2) ? get_float3(val) : o->cx;
	o->cy = !ft_strncmp(n, "cy", 2) ? get_float3(val) : o->cy;
	o->canvas = !ft_strncmp(n, "canvas", 6) ? get_int2(val) : o->canvas;
}


static void			get_camera_info(json_value *value, t_camera *c)
{
	unsigned int	i;
	char			*n;

	i = 0;
	while (i < value->u.object.length - 1)
	{
		n = value->u.object.values[i].name;
		printf("%s\n",n);
		get_camera_details(c, n, value->u.object.values[i].value);
		i++;
	}
}

void				parse_camera(json_value *value, t_scene *s)
{
	ft_bzero(&s->camera, sizeof(s->camera));
	if (value->u.array.values[0]->type != json_object)
		ft_error("Not valid json camera.");
	get_camera_info(value->u.array.values[0], &s->camera);
}

void 				print_cam(t_camera *o)
{
		printf("origin : { %f %f %f }\n", o->origin.s0, o->origin.s1, o->origin.s2);
		printf("dir : { %f %f %f }\n", o->dir.s0, o->dir.s1, o->dir.s2);
		printf("cx : { %f %f %f }\n", o->cx.s0, o->cx.s1, o->cx.s2);
		printf("cy : { %f %f %f }\n", o->cy.s0, o->cy.s1, o->cy.s2);
		printf("canvas : { %i %i }\n", o->canvas.s0, o->canvas.s1);
}
