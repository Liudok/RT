
#include "../../include/parser.h"
#include <sys/stat.h>

void 			delete_old_scene(t_rt *s)
{
	free(s->scene.objs);
}

static char		*read_file(const char *filename, int size)
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

void				file_choosing(t_rt *s)
{
	char const		*lFilterPatterns[2] = { "*.json", "*.rt" };
	struct stat		k;
	char			*file_str;

	s->scene.file = (char *)tinyfd_openFileDialog("Please choose .json file", "", 2, lFilterPatterns, NULL, 0);
	if (s->scene.file)
	{
		if (ft_strcmp(".json", (s->scene.file + ft_strlen(s->scene.file) - 5)))
			ft_error("Wrong file format. Please choose file *.json");
		if ((stat(s->scene.file, &k) != 0) || !(S_ISREG(k.st_mode)))
			ft_error("File not found.");
		else
		{
			delete_old_scene(s);
			file_str = read_file(s->scene.file, k.st_size);
			start_parsing(file_str, &s->scene, k.st_size);
			init_camera(s);
			reinit_opencl(s);
		}
	}
}

void	init_default_scene(t_rt *rt)
{
	struct stat		k;
	char			*file_str;
	uint 			size;

	rt->scene.file = "scenes/default.json";
	if ((stat(rt->scene.file, &k) != 0) || !(S_ISREG(k.st_mode)))
		ft_error("Default file not found at scenes/default.json");
	size = k.st_size;
	file_str = read_file(rt->scene.file, size);
	start_parsing(file_str, &rt->scene, size);
	init_camera(rt);
}
