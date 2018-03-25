
#include "panels.h"
#include "rt.h"

// void		parser(char *line, t_scene *scene, int *i)
// {
// 	if (!ft_strncmp("o ", line, 2))
// 	{
// 		scene->objs[i].type = get_fig_type(ft_strchr(line, ' '));
// 		(*i)++;
// 	}
// 	else if(!ft_strncmp("col ", line, 4))
// 		scene->objs[*i - 1].col = get_fig_col(ft_strchr(line, ' '));
// 	else if(!ft_strncmp("pos ", line, 4))
// 		scene->objs[*i - 1].pos = get_fig_pos(ft_strchr(line, ' '));
// 	else if(!ft_strncmp("rad ", line, 4))
// 		scene->objs[*i - 1].rad = ft_atoi(ft_strchr(line, ' '));
// }

// void		start_parsing(t_sdl *s)
// {
// 	int fd;
// 	char *line;
// 	t_scene scene;
// 	int i;

// 	i = 0;
// 	fd = open(s->file, O_RDONLY);
// 	if (fd < 0)
// 		ft_error(MES2);
// 	if (get_next_line(fd, &line) == 1)
// 		scene.objects_num = ft_atoi(line);
// 	free(line);
// 	scene.objs = (t_obj*)malloc(sizeof(t_obj) * scene.objects_num);
// 	while (get_next_line(fd, &line) == 1)
// 	{
// 		parser(line, &scene, &i);
// 		free(line);
// 	}
// 	close(fd);
// }
