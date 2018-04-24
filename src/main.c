/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 12:14:39 by lberezyn          #+#    #+#             */
/*   Updated: 2018/04/24 16:46:38 by lberezyn         ###   ########.fr       */
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
		ft_error("Failed SDL initialization");
	init_default_scene(&s);
	if (!run_ui(&s))
		ft_error("Running failure");
	destroy(&s);
	return (0);
}

void		pt_check_error(int flag, char *err1, char *err2)
{
	if (flag)
	{
		if (err2 != NULL)
			fprintf(stderr, "%s %s\n", err1, err2);
		else
			fprintf(stderr, "%s\n", err1);
		exit(0);
	}
}

void		ft_error(char *s)
{
	ft_putendl_fd(s, 2);
	exit(1);
}

void	destroy(t_rt *pt)
{
	free(pt->icon);
	SDL_DestroyTexture(pt->sdl.canvas);
	SDL_DestroyRenderer(pt->sdl.renderer);
	SDL_DestroyWindow(pt->sdl.win);
	rt_cl_free_kernel(&pt->kernel);
	rt_cl_free(&pt->info);
	clReleaseMemObject(pt->scene.objs_mem);
	clReleaseMemObject(pt->seeds);
	clReleaseMemObject(pt->colors);
	clReleaseMemObject(pt->pixels_mem);
	free(pt->sdl.pixels);
	SDL_Quit();
}
