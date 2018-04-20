/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 12:20:12 by lberezyn          #+#    #+#             */
/*   Updated: 2018/04/20 20:28:00 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/panels.h"

int 			load_all_textures(t_rt *s)
{
	if (!(s->sdl.canvas = SDL_CreateTexture(s->sdl.renderer,
								SDL_PIXELFORMAT_ARGB8888,
								SDL_TEXTUREACCESS_STATIC,
								s->sdl.win_w, s->sdl.win_h)))
	{
		ft_putendl_fd("failed to initiate texture in SDL", 2);
		return (0);
	}
	s->textures[0] = load_texture("src/img/dark_pixel2.png", s);
	s->textures[1] = load_texture("src/img/dark_pixel.png", s);
	s->textures[2] = load_texture("src/img/rama.png", s);
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
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		s->sdl.win_w, s->sdl.win_h, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI);
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
	create_buttons(s);
	return (1);
}



int 			run_ui(t_rt *s)
{
	int running = 1;
	char flag = 0;

//	size_t			job_size = s->win_w * s->win_h;

	printf("initioated succesfully");
//	init_kernel(s);

//
	while (running)
	{
		SDL_Event evt;
		while (SDL_PollEvent(&evt))
		{
			if (evt.type == SDL_QUIT || (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE))
				running = 0;
			else if (evt.type == SDL_KEYDOWN )
			{
				if (evt.key.keysym.sym == SDLK_UP)
					flag = 1;
				else if (evt.key.keysym.sym == SDLK_DOWN)
					flag = 2;
				else if (evt.key.keysym.sym == SDLK_LEFT)
					flag = 3;
			}
			else if (evt.type == SDL_MOUSEBUTTONDOWN)
			{
				check_pressing(s, evt.button.x, evt.button.y);
				render_buttons(s);
			}
		}

//		for (int i = 0; i < 2; i++)
//			rt_cl_push_task(&s->extended, &job_size);
//		rt_cl_push_task(&s->smooth, &job_size);
// 		rt_cl_device_to_host(&s->info, s->out, pixels, job_size * sizeof(int));

//		clSetKernelArg(s->kernel.kernel, 3, sizeof(cl_uint), &s->samples);
//		rt_cl_push_task(&s->kernel, &job_size);
//
//		rt_cl_device_to_host(&s->info, s->pixels_mem, s->pixels, job_size * sizeof(int));
//
//		rt_cl_join(&s->info);

		set_bg(s);
//		SDL_RenderPresent(s->renderer);
		// if (s->file != NULL && s->go)
		// {
		// 	s->go = 0;
		// 	// start_parsing(s);
		// }
		// if (flag == 1)
		// {
		// 	s->surf = SDL_LoadBMP(tinyfd_openFileDialog("Please choose .bmp file", "", 2, lFilterPatterns, NULL, 0));
		// 	txt = SDL_CreateTextureFromSurface(s->renderer, s->surf);
		// 	SDL_FreeSurface(s->surf);
		// 	SDL_RenderCopy(s->renderer, txt, NULL, NULL);
		// 	SDL_RenderPresent(s->renderer);
  //     			// SDL_Delay(2000);
		// }
		// else if (flag == 2)
		// {
		// 	// s->surf = SDL_LoadBMP("tigr.bmp");
		// 	// BlueShapes = SDL_CreateTextureFromSurface(s.renderer, s->surf);
		// 	// SDL_FreeSurface(s->surf);
		// 	// SDL_RenderCopy(s.renderer, BlueShapes, &SrcR, &DestR);
		// 	// SDL_RenderPresent(s.renderer);
		// }
		// if (flag == 3)
		// {
		// 	// SDL_Surface* screenSurface = NULL;
		// 	// s->surf = IMG_Load(tinyfd_openFileDialog("Please choose .bmp file", "", 2, lFilterPatterns, NULL, 0));
		// 	// SDL_Texture* BlueShapes = SDL_CreateTextureFromSurface(s->renderer, s->surf);
		// 	// SDL_FreeSurface(s->surf);
		// 	// SDL_RenderCopy(s->renderer, load_texture(icons[i], s), NULL, NULL);
		// 	// SDL_RenderPresent(s.renderer);
		// }
		// flag = 0;
		// SDL_RenderClear(s->renderer);
		// s->surf = SDL_CreateRGBSurfaceFrom((void*)s->data,
		// 	a->scene->image_width, a->scene->image_height, 32,
		// 	a->scene->image_width * 4, 0, 0, 0, 0);
		// s->surf = SDL_LoadBMP("tigr.bmp");
		// set_panels(s->renderer, s->surf);
		// s->surf = SDL_CreateRGBSurface(0, 400, 800, 32, 48, 214, 250, 0);
		// txt = SDL_CreateTextureFromSurface(s->renderer, s->surf);
		// txt = load_texture("folder.png", s);
		// SDL_RenderCopy(s->renderer, load_texture("gal.png", s), NULL, NULL);
		SDL_RenderPresent(s->sdl.renderer);
	}
	SDL_FreeSurface(s->sdl.surf);
	rt_cl_free_kernel(&s->kernel);
	rt_cl_free(&s->info);
	SDL_DestroyTexture(s->sdl.canvas);
	SDL_DestroyRenderer(s->sdl.renderer);
	SDL_DestroyWindow(s->sdl.win);
	SDL_Quit();
	return (1);
}