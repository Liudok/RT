/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <lberezyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 14:55:04 by lberezyn          #+#    #+#             */
/*   Updated: 2017/11/29 18:06:28 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_try_to_read(int fd, char **line, char **str, int *flag)
{
	int				ret;
	char			buff[BUFF_SIZE + 1];
	int				len;
	char			*temp;

	if ((ret = read(fd, buff, BUFF_SIZE)) == -1)
		return (-1);
	buff[ret] = '\0';
	len = 0;
	*flag = 0;
	ft_bzero(*str, ft_strlen(*str));
	while (buff[len] != '\n' && buff[len] != '\0' && buff[len] != -1)
		len++;
	if (len < BUFF_SIZE && (buff[len] == '\n') && (temp = *str))
	{
		*str = ft_strdup(buff + len + 1);
		free(temp);
		*flag = 1;
	}
	buff[len] = '\0';
	temp = *line;
	*line = ft_strjoin(*line, buff);
	free(temp);
	return (ret);
}

t_listik			*ft_check_fd(int fd, t_listik **list)
{
	t_listik		*new;

	new = NULL;
	if (list && *list)
	{
		new = *list;
		while (new)
		{
			if (new->fd == fd)
				return (new);
			new = new->next;
		}
	}
	if (!(new = (t_listik*)malloc(sizeof(t_listik))))
		return (NULL);
	if (!(new->str = ft_strnew(BUFF_SIZE)))
	{
		free(new);
		return (NULL);
	}
	*new->str = '\0';
	new->next = *list;
	*list = new;
	new->fd = fd;
	return (new);
}

int					get_next_line(const int fd, char **line)
{
	static t_listik	*list;
	t_listik		*current;
	char			*s;
	int				ret;
	int				flag_n;

	if (fd < 0 || !line || BUFF_SIZE < 1 || !(current = ft_check_fd(fd, &list)))
		return (-1);
	if ((s = ft_strchr(current->str, '\n')))
	{
		s[0] = '\0';
		*line = ft_strdup(current->str);
		ft_strcpy(current->str, s + 1);
		return (*line ? 1 : -1);
	}
	*line = ft_strdup(current->str);
	ret = BUFF_SIZE;
	while (ret == BUFF_SIZE)
	{
		if ((ret = ft_try_to_read(fd, line, &current->str, &flag_n)) == -1)
			return (-1);
		if (flag_n == 1 || (ret < BUFF_SIZE && ft_strlen(*line)))
			return (1);
	}
	return (0);
}
