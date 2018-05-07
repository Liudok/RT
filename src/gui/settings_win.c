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

int 		this_figure_props(t_obj_type type)
{
	if (type == 0)
		return (22);
	else if (type == 1)
		return (24);
	else if (type == 2 || type == 5)
		return (26);
	else if (type == 3)
		return (27);
	else if (type == 4 || type == 7 || type == 10)
		return (25);
	else if (type == 6)
		return (27);
	else
		return (0);
}

static int 		this_figure_small_props(t_obj_type type)
{
	if (type == 0)
		return (5);
	else if (type == 1 || type == 7)
		return (5);
	else if (type == 2 || type == 5)
		return (7);
	else if (type == 3)
		return (8);
	else if (type == 4)
		return (6);
	else if (type == 6 || type == 10)
		return (6);
	else
		return (0);
}


void		render_settings_bg(t_sdl *sdl, t_rec *recs, int prop, int small_prop)
{
	int		i;

	i = 0;
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
	int		small_prop;

	running = 1;
	create_settings_win(&sdl);
	prop = this_figure_props(rt->scene.objs[i].type);
	small_prop = this_figure_small_props(rt->scene.objs[i].type);
	recs = (t_rec*)malloc(sizeof(t_rec) * prop);
	ft_bzero(recs, sizeof(recs));
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

			}
		}
		render_settings_bg(&sdl, recs, prop, small_prop);
	}
	free(recs);
	SDL_DestroyRenderer(sdl.renderer);
	SDL_DestroyWindow(sdl.win);
}
