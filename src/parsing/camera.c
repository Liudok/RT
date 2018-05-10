
#include <OpenCL/opencl.h>
# include "../../include/parser.h"

static void			get_camera_info(json_value *value, t_camera *c)
{
	unsigned int	i;
	char			*n;

	i = 0;
	while (i < value->u.object.length)
	{
		n = value->u.object.values[i].name;
		c->base_origin = !ft_strncmp(n, "origin", 6) ?
					get_float3(value->u.object.values[i].value) : c->base_origin;
		c->base_dir = normalize(!ft_strncmp(n, "dir", 3) ?
				 get_float3(value->u.object.values[i].value) : c->base_dir);
		c->ambient = !ft_strncmp(n, "ambient", 6) ?
					 get_float3(value->u.object.values[i].value) : c->ambient;
		i++;
	}
}

void				parse_camera(json_value *value, t_scene *s)
{
	ft_bzero(&s->camera, sizeof(s->camera));
	s->camera.rotate.x = 0;
	s->camera.rotate.y = 0;
	s->camera.ambient = (float3){{0, 0, 0}};
	if (value->u.array.values[0]->type != json_object)
		ft_error("Not valid json camera.");
	get_camera_info(value->u.array.values[0], &s->camera);
    if (s->camera.ambient.s0 > 1)
        s->camera.ambient.s0 = 1;
    if (s->camera.ambient.s1 > 1)
        s->camera.ambient.s1 = 1;
    if (s->camera.ambient.s2 > 1)
        s->camera.ambient.s2 = 1;
    if (s->camera.ambient.s0 < 0)
        s->camera.ambient.s0 = 0;
    if (s->camera.ambient.s1 < 0)
        s->camera.ambient.s1 = 0;
    if (s->camera.ambient.s2 < 0)
        s->camera.ambient.s2 = 0;
}

void				init_camera(t_rt *pt, float3 origin)
{
	t_camera	*cam;

	cam = &pt->scene.camera;
	cam->canvas = (int2){{pt->sdl.win_w, pt->sdl.win_h}};
	cam->origin = origin;
	cam->dir = cam->base_dir;
	cam->cx = (float3){{cam->canvas.x * .5135f / (float)cam->canvas.y, 0, 0}};
	cam->cy = vmul(normalize(cross(cam->cx, cam->dir)), .5135f);
}
