/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 12:20:12 by lberezyn          #+#    #+#             */
/*   Updated: 2018/04/27 15:17:20 by skamoza          ###   ########.fr       */
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
	// ADD PROTECTION TO CHECK IF FILES ARE OK
	s->textures_img[0] = IMG_Load("src/img/earth.jpg");
	s->textures_img[1] = IMG_Load("src/img/earth_normal.jpg");
	s->textures_img[2] = IMG_Load("src/img/earth_light.jpg");
	s->textures_img[3] = IMG_Load("src/img/earth_clouds.jpg");
	s->textures_img[4] = IMG_Load("src/img/brickwall.jpg");
	s->textures_img[5] = IMG_Load("src/img/brickwall_normal.jpg");
	s->textures_img[6] = IMG_Load("src/img/TennisBallColor.jpg");
	s->textures_img[7] = IMG_Load("src/img/TennisBallNormal.jpg");
	s->textures_img[8] = IMG_Load("src/img/BeachBallColor.jpg");
	s->textures_img[9] = IMG_Load("src/img/BeachBallTransp.jpg");
	s->textures_img[10] = IMG_Load("src/img/SoftballColor.jpg");
	s->textures_img[11] = IMG_Load("src/img/SoftballNormal.jpg");
	s->textures_img[12] = IMG_Load("src/img/processor.jpg");
	s->textures_img[13] = IMG_Load("src/img/BallCue.jpg");
	s->textures_img[14] = IMG_Load("src/img/Ball1.jpg");
	s->textures_img[15] = IMG_Load("src/img/Ball2.jpg");
	s->textures_img[16] = IMG_Load("src/img/Ball3.jpg");
	s->textures_img[17] = IMG_Load("src/img/Ball4.jpg");
	s->textures_img[18] = IMG_Load("src/img/Ball5.jpg");
	s->textures_img[19] = IMG_Load("src/img/Ball6.jpg");
	s->textures_img[20] = IMG_Load("src/img/Ball7.jpg");
	s->textures_img[21] = IMG_Load("src/img/Ball8.jpg");
	s->textures_img[22] = IMG_Load("src/img/Ball9.jpg");
	s->textures_img[23] = IMG_Load("src/img/Ball10.jpg");
	s->textures_img[24] = IMG_Load("src/img/Ball11.jpg");
	s->textures_img[25] = IMG_Load("src/img/Ball12.jpg");
	s->textures_img[26] = IMG_Load("src/img/Ball13.jpg");
	s->textures_img[27] = IMG_Load("src/img/Ball14.jpg");
	s->textures_img[28] = IMG_Load("src/img/BasketballColor.jpg");
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
	s->sdl.renderer = SDL_CreateRenderer(s->sdl.win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
	int fig;

	running = 1;
	init_opencl(s);
	SDL_Event evt;
	while (running)
	{
		while (SDL_PollEvent(&evt))
		{
			if (is_quit(evt))
				running = 0;
			else if (is_window_resizable(evt))
				handling_window_resizable(s, evt);
			else if (evt.type == SDL_KEYDOWN)
				on_event(s, &evt);
			else if (evt.type == SDL_KEYUP)
				off_event(s, &evt);
			else if (evt.type == SDL_MOUSEBUTTONDOWN)
			{
				check_pressing(s, evt.button.x, evt.button.y);
				render_buttons(s);
				fig = mouse_ray(s, evt.button.x, evt.button.y);
				if (fig > 0)
				{
					printf("figure2 = %i\n", fig);
//					show_settings(s);
				}
			}
		}
		if (is_camera_event(s))
			update_camera(s);
		set_bg(s);
	}
	return (1);
}
