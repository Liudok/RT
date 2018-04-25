/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 12:20:12 by lberezyn          #+#    #+#             */
/*   Updated: 2018/04/25 12:31:23 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/panels.h"

int 			load_all_textures(t_rt *s)
{
	if (!(s->sdl.canvas = SDL_CreateTexture(s->sdl.renderer,
								SDL_PIXELFORMAT_ARGB8888,
								SDL_TEXTUREACCESS_TARGET,
								s->sdl.win_w, s->sdl.win_h)))
	{
		ft_putendl_fd("failed to initiate texture in SDL", 2);
		return (0);
	}
	s->textures[0] = load_texture("src/img/dark_pixel2.png", s);
	s->textures[1] = load_texture("src/img/dark_pixel.png", s);
	s->textures[2] = load_texture("src/img/rama.png", s);
	s->textures_img[0] = IMG_Load("src/img/brickwall.jpg");
	s->textures_img[1] = IMG_Load("src/img/brickwall_normal.jpg");
	s->textures_img[2] = IMG_Load("src/img/earth.jpg");
	return (1);
}

int 			sdl_init_everything(t_rt *s)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		ft_putendl_fd("failed to initiate SDL", 2);
		return (0);
	}
	s->sdl.win = SDL_CreateWindow("RT",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		s->sdl.win_w, s->sdl.win_h,
		SDL_WINDOW_RESIZABLE);
	if (s->sdl.win == NULL)
	{
		ft_putendl_fd("failed to initiate WIN in SDL", 2);
		return (0);
	}
	s->sdl.renderer = SDL_CreateRenderer(s->sdl.win, -1, SDL_RENDERER_ACCELERATED);
	if (s->sdl.renderer == NULL)
	{
		ft_putendl_fd("failed to initiate renderer in SDL", 2);
		return (0);
	}
	if (!load_all_textures(s))
		return (0);
	SDL_RenderSetLogicalSize(s->sdl.renderer, s->sdl.win_w, s->sdl.win_h);
	SDL_SetRenderDrawColor(s->sdl.renderer, 0, 255, 0, 255);
	s->sdl.pixels = (int*)malloc(sizeof(int) * (s->sdl.win_w * s->sdl.win_h));
	create_buttons(s);
	return (1);
}

int 			run_ui(t_rt *s)
{
	int running;

	running = 1;
	init_opencl(s);
	SDL_Event evt;
	while (running)
	{
		while (SDL_PollEvent(&evt))
		{
			if (isQuit(evt))
				running = 0;
			else if (isWindowResizable(evt))
				handlingWindowResizable(s, evt);
			else if (evt.type == SDL_KEYDOWN)
				onEvent(s, &evt);
			else if (evt.type == SDL_KEYUP)
				offEvent(s, &evt);
			else if (evt.type == SDL_MOUSEBUTTONDOWN)
			{
				check_pressing(s, evt.button.x, evt.button.y);
				render_buttons(s);
			}
		}
		if (isCameraEvent(s))
			updateCamera(s);
		set_bg(s);
	}
	return (1);
}
