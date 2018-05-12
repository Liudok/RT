/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_to_json.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 07:09:51 by skamoza           #+#    #+#             */
/*   Updated: 2018/05/12 07:13:45 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/opencl.h>
#include "../../include/panels.h"

void			dprint_material(t_material material, int fd)
{
	char *mat;

	if (material == 0)
		mat = "diffuse";
	else if (material == 1)
		mat = "specular";
	else if (material == 2)
		mat = "glass";
	else if (material == 3)
		mat = "emission";
	else if (material == 4)
		mat = "transparent";
	else
		mat = "diffuse";
	dprintf(fd, "\t\t\t\"material\": \"%s\",\n", mat);
}

static void		save_objs(int fd, t_object *o, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		if (i == 0)
			dprintf(fd, "{\n\t\t\t\"type\": \"%s\",\n", type_to_str(o[i].type));
		else
			dprintf(fd, "\t\t{\n\t\t\t\"type\": \"%s\",\n",
					type_to_str(o[i].type));
		dprint_material(o[i].material, fd);
		dprintf(fd, "\t\t\t\"roughness\": %f,\n", o[i].roughness);
		dprintf(fd, "\t\t\t\"ior\": %f,\n", o[i].ior);
		dprintf(fd, "\t\t\t\"color\": [%f, %f, %f],\n", o[i].color.s0,
				o[i].color.s1, o[i].color.s2);
		print_prim_info(fd, &o[i]);
		dprintf(fd, "\t\t\t\"texture\": [%hhu, %hhu, %hhu, %hhu]\n",
	o[i].texture.s0, o[i].texture.s1, o[i].texture.s2, o[i].texture.s3);
		if (i != n - 1)
			dprintf(fd, "\t\t},\n");
		else
			dprintf(fd, "\t\t}\n\t],\n\t\"camera\": [{\n");
		i++;
	}
}

void			save_scene_to_file(t_rt *s)
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
	dprintf(fd, "\t\t\"origin\": [%f, %f, %f],\n", s->scene.camera.origin.s0,
			s->scene.camera.origin.s1, s->scene.camera.origin.s2);
	dprintf(fd, "\t\t\"dir\": [%f, %f, %f],\n", s->scene.camera.dir.s0,
			s->scene.camera.dir.s1, s->scene.camera.dir.s2);
	dprintf(fd, "\t\t\"ambient\": [%f, %f, %f]\n", s->scene.camera.ambient.s0,
			s->scene.camera.ambient.s1, s->scene.camera.ambient.s2);
	dprintf(fd, "\t}]\n}");
	close(fd);
}
