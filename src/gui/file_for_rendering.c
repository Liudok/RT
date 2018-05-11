/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_for_rendering.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 17:18:02 by skamoza           #+#    #+#             */
/*   Updated: 2018/05/10 17:41:14 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include <sys/stat.h>

static char			*read_file(const char *filename, int size)
{
	int			fd;
	char		*file_content;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error("Error opening the file.");
	file_content = (char*)malloc(size + 1);
	if (file_content == NULL)
		ft_error("Memory error: unable to allocate.");
	if (read(fd, file_content, size + 1) < 0)
	{
		close(fd);
		free(file_content);
		ft_error("Error in file reading.");
	}
	close(fd);
	file_content[size] = '\0';
	return (file_content);
}

static void			recreate_scene(t_rt *rt, struct stat *k)
{
	t_scene			tmp_scene;
	char			*file_str;

	tmp_scene = rt->scene;
	file_str = read_file(rt->scene.file, k->st_size);
	start_parsing(file_str, &tmp_scene, k->st_size, rt);
	if (g_error_flag)
		ft_putendl_fd("Not valid map.", 2);
	else
	{
		free(rt->scene.objs);
		rt->scene = tmp_scene;
		init_camera(rt, tmp_scene.camera.base_origin);
		reinit_opencl(rt);
	}
}

void				file_choosing(t_rt *rt)
{
	char const		*l_filter_patterns[2] = { "*.json", "*.rt" };
	struct stat		k;

	rt->scene.file = (char *)tinyfd_openFileDialog("Please choose .json file",
			"", 2, l_filter_patterns, NULL, 0);
	if (rt->scene.file)
	{
		if (ft_strstr(".json", rt->scene.file))
		{
			ft_putendl("Wrong file format. Please choose file *.json");
			choosing_dialog(rt);
		}
		if ((stat(rt->scene.file, &k) != 0) || !(S_ISREG(k.st_mode)))
			ft_error("File not found.");
		else
			recreate_scene(rt, &k);
	}
}

void				choosing_dialog(t_rt *rt)
{
	struct stat		k;
	const char		*l_filter_patterns[2] = {"*.json", "*.rt"};

	rt->scene.file = (char *)tinyfd_openFileDialog(
			"Please choose .json file", "", 2, l_filter_patterns, NULL, 0);
	if (rt->scene.file)
	{
		while (ft_strstr(".json", rt->scene.file))
		{
			ft_putendl("Wrong file format. Please choose file *.json");
			rt->scene.file = (char *)tinyfd_openFileDialog("Please choose .json"
					" file", "", 2, l_filter_patterns, NULL, 0);
			if (rt->scene.file == NULL)
				break ;
		}
		if (rt->scene.file == NULL ||
				(stat(rt->scene.file, &k) != 0) || !(S_ISREG(k.st_mode)))
			ft_error("File not found.");
	}
	else
		ft_error("Good bye");
}

void				init_default_scene(t_rt *rt)
{
	struct stat		k;
	char			*file_str;
	uint			size;

	rt->scene.file = "scenes/shlak.json";
	if ((stat(rt->scene.file, &k) != 0) || !(S_ISREG(k.st_mode)))
	{
		ft_putendl("Default file not found at scenes/default.json");
		choosing_dialog(rt);
		stat(rt->scene.file, &k);
	}
	size = k.st_size;
	file_str = read_file(rt->scene.file, size);
	start_parsing(file_str, &rt->scene, size, rt);
	init_camera(rt, rt->scene.camera.base_origin);
}
