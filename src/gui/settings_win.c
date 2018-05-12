/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_win.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:51:45 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/01 18:51:49 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/opencl.h>
#include "../../include/panels.h"

void		create_settings_win(t_sdl *sdl)
{
	sdl->win = SDL_CreateWindow("Settings",
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								500, 500,
								SDL_WINDOW_RESIZABLE);
	sdl->renderer = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_ACCELERATED);
	sdl->canvas = SDL_CreateTexture(sdl->renderer,
									SDL_PIXELFORMAT_ARGB8888,
									SDL_TEXTUREACCESS_TARGET,
									500, 500);
	SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 25, 38);
}

int			render_settings_bg(t_sdl *sdl, t_rec *recs, int prop, int type)
{
	int		i;
	int		small_prop;

	i = 0;
	small_prop = this_figure_small_props(type);
	SDL_RenderClear(sdl->renderer);
	while (i < prop)
	{
		if (recs[i].texture != NULL && (i < small_prop || i > 9))
		{
			SDL_RenderCopy(sdl->renderer, recs[i].texture,
				NULL, &recs[i].rect);
		}
		i++;
	}
	SDL_RenderPresent(sdl->renderer);
	return (1);
}

void		inner_loop(t_rt *rt, t_sdl *sdl, t_rec *recs, const int *r)
{
	int			running;
	SDL_Event	evt;
	int			btn;

	btn = -1;
	running = 1;
	while (running)
	{
		while (SDL_PollEvent(&evt))
			if (is_quit(evt))
				running = 0;
			else if (evt.type == SDL_KEYDOWN)
				on_event(rt, &evt);
			else if (evt.type == SDL_KEYUP)
				off_event(rt, &evt);
			else if (evt.type == SDL_MOUSEBUTTONDOWN && (btn =
		check_pressing_setting(r[0], recs, evt.button.x, evt.button.y)) >= 0)
			{
				change_value(&rt->scene.objs[r[1]], btn);
				real_values(&rt->scene.objs[r[1]], sdl, (t_rec *)recs);
				btn = -10;
			}
		render_settings_bg(sdl, recs, r[0], rt->scene.objs[r[1]].type);
	}
	btn == -10 ? reinit_opencl(rt) : 0;
}

void		start_settings_win(t_rt *rt, int i)
{
	t_sdl		sdl;
	const int	r[] = {this_figure_props(rt->scene.objs[i].type), i};
	t_rec		*recs;

	if (!(r[0]))
		return ;
	recs = malloc(sizeof(t_rec) * r[0]);
	ft_bzero(recs, sizeof(recs));
	create_settings_win(&sdl);
	create_settings_textures(rt, &sdl, recs, i);
	real_values(&rt->scene.objs[i], &sdl, recs);
	inner_loop(rt, &sdl, recs, r);
	free(recs);
	SDL_DestroyRenderer(sdl.renderer);
	SDL_DestroyWindow(sdl.win);
}
