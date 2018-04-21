/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 12:14:39 by lberezyn          #+#    #+#             */
/*   Updated: 2018/04/21 11:28:25 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int			main(void)
{
	t_rt	s;

	s.sdl.win_w = WINDOW_WIDTH;
	s.sdl.win_h = WINDOW_HEIGHT;
	s.scene.file = NULL;
	if (!sdl_init_everything(&s))
	{
		printf("Failed SDL initialization");
		return (1);
	}
	init_default_scene(&s);
	if (!run_ui(&s))
	{
		printf("Running failure");
		return (1);
	}
	return (0);
}

void		ft_error(char *s)
{
	ft_putendl_fd(s, 2);
	exit(0);
}
