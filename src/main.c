/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 12:14:39 by lberezyn          #+#    #+#             */
/*   Updated: 2018/03/25 12:14:41 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			main(void)
{
	t_sdl	s;

	if (!sdl_init_everything(&s))
	{
		printf("Failed SDL initialization");
		return (1);
	}
	if (!run_ui(&s))
	{
		printf("Runnning failure");
		return (1);
	}
	return (0);
}

void		ft_error(char *s)
{
	ft_putendl_fd(s, 2);
	exit(0);
}
