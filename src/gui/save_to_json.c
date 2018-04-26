
#include "../../include/panels.h"

static void	save_objs(int fd, t_object *o, int n)
{
	int i = 0;
	while (i < n)
	{
		if (i == 0)
			dprintf(fd, "{\n\t\t\t\"type\": \"%s\",\n", type_to_str(o[i].type));
		else
			dprintf(fd, "\t\t{\n\t\t\t\"type\": \"%s\",\n", type_to_str(o[i].type));
		dprintf(fd,"\t\t\t\"material\": [%f, %f, %f, %f],\n", o[i].material.s0, o[i].material.s1, o[i].material.s2, o[i].material.s3);
		dprintf(fd,"\t\t\t\"color\": [%f, %f, %f],\n", o[i].color.s0, o[i].color.s1, o[i].color.s2);
		print_prim_info(fd, o, i);
//		dprintf(fd,"\t\t\t\"texture\": %i\n", o[i].texture);
		if (i != n - 1)
			dprintf(fd, "\t\t},\n");
		else
			dprintf(fd, "\t\t}\n\t],\n\t\"camera\": [{\n");
		i++;
	}
}

void 			save_scene_to_file(t_rt *s)
{
	const char	*save;
	const char	*format[1] = { "*.json" };
	int			fd;

	save = tinyfd_saveFileDialog("", "new_scene.json", 1, format, NULL);
	if (save == NULL)
		return ;
	fd = open(save, O_RDWR | O_TRUNC | O_CREAT, 0644);
	dprintf(fd, "{\n\t\"objects\": [");
	save_objs(fd, s->scene.objs, s->scene.objnum);
	dprintf(fd,"\t\t\"origin\": [%f, %f, %f],\n", s->scene.camera.origin.s0, s->scene.camera.origin.s1, s->scene.camera.origin.s2);
	dprintf(fd,"\t\t\"dir\": [%f, %f, %f]\n", s->scene.camera.dir.s0, s->scene.camera.dir.s1, s->scene.camera.dir.s2);
	dprintf(fd, "\t}]\n}");
	close(fd);
}
