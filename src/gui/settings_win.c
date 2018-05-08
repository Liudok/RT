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
								500, 400,
								SDL_WINDOW_RESIZABLE);
	sdl->renderer = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_ACCELERATED);
	sdl->canvas = SDL_CreateTexture(sdl->renderer,
									SDL_PIXELFORMAT_ARGB8888,
									SDL_TEXTUREACCESS_TARGET,
									500, 400);
	SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 25, 38);
}

void		render_settings_bg(t_sdl *sdl, t_rec *recs, int prop, int type)
{
	int		i;
	int		small_prop;

	i = 0;
	small_prop = this_figure_small_props(type);
	SDL_RenderClear(sdl->renderer);
	while (i < prop)
	{
		if (recs[i].texture != NULL && (i < small_prop || i > 7))
		{
			SDL_RenderCopy(sdl->renderer, recs[i].texture,
						   NULL, &recs[i].rect);
		}
		i++;
	}
	SDL_RenderPresent(sdl->renderer);
}


void		start_settings_win(t_rt* rt, int i)
{
	t_sdl	sdl;
	int		running;
	t_rec	*recs;
	int		prop;
	int		btn;

	running = 1;
	btn = -1;
	prop = this_figure_props(rt->scene.objs[i].type);
	if (prop == 0)
		return;
	recs = (t_rec*)malloc(sizeof(t_rec) * prop);
	ft_bzero(recs, sizeof(recs));
	create_settings_win(&sdl);
	create_settings_textures(rt, &sdl, recs, i);
	real_create_settings_textures(rt, &sdl, recs, i);
	SDL_Event evt;
	while (running)
	{
		while (SDL_PollEvent(&evt))
		{
			if (is_quit(evt))
				running = 0;
			else if (evt.type == SDL_KEYDOWN)
				on_event(rt, &evt);
			else if (evt.type == SDL_KEYUP)
				off_event(rt, &evt);
			else if (evt.type == SDL_MOUSEBUTTONDOWN)
			{
				btn = check_pressing_setting(prop, recs, evt.button.x, evt.button.y);
				if (btn >= 0)
				{
					change_value(rt, i, btn);
					real_create_settings_textures(rt, &sdl, recs, i);
					btn = -10;
				}
			}
		}
		render_settings_bg(&sdl, recs, prop, rt->scene.objs[i].type);
	}
	if (btn == -10)
		reinit_opencl(rt);
	free(recs);
	SDL_DestroyRenderer(sdl.renderer);
	SDL_DestroyWindow(sdl.win);
}
