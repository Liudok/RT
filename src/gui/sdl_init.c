/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 12:20:12 by lberezyn          #+#    #+#             */
/*   Updated: 2018/04/22 12:13:32 by lberezyn         ###   ########.fr       */
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

void 				print_cam(t_camera *o);
void 				print_obj(t_object *o, int n);

//static int	pull_event(SDL_Event *e)
//{
//	while (SDL_PollEvent(e))
//	{
//		if (e->type == SDL_QUIT ||
//			(e->type == SDL_WINDOWEVENT && e->window.event == SDL_WINDOWEVENT_RESIZED) ||
//			(e->type == SDL_KEYDOWN && !e->key.repeat) ||
//			(e->type == SDL_KEYUP && !e->key.repeat))
//			return (TRUE);
//	}
//	return (FALSE);
//}

int 			run_ui(t_rt *s)
{
	int running = 1;

	s->scene.camera.canvas = (int2){{s->sdl.win_w, s->sdl.win_h}};
	s->scene.camera.cx = (float3){{s->scene.camera.canvas.x * .5135f / (float)s->scene.camera.canvas.y, 0, 0}};
	s->scene.camera.cy = vmul(normalize(cross(s->scene.camera.cx, s->scene.camera.dir)), .5135);

	init_opencl(s);
//	printf("initiated succesfully\n");
//	print_cam(&s->scene.camera);
//	print_obj(s->scene.objs, s->scene.objnum);
	SDL_Event evt;
	while (running)
	{	
		while (SDL_PollEvent(&evt))
		{
			if (evt.type == SDL_QUIT || (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE))
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
			if (isCameraEvent(s))
				updateCamera(s);
		}
		clSetKernelArg(s->kernel.kernel, 6, sizeof(cl_uint), &s->samples);
		rt_cl_push_task(&s->kernel, &s->job_size);
		rt_cl_device_to_host(&s->info, s->pixels_mem, s->sdl.pixels, s->job_size * sizeof(int));
		SDL_UpdateTexture(s->sdl.canvas, NULL, s->sdl.pixels, s->sdl.win_w << 2);
		SDL_RenderClear(s->sdl.renderer);
		SDL_RenderCopy(s->sdl.renderer, s->sdl.canvas, NULL, NULL);
		fprintf(stderr, " samples per pixel -> %d\r", s->samples);

		set_panel(s);
//		rt_cl_join(&s->info);
		SDL_RenderPresent(s->sdl.renderer);
//		set_bg(s);
		s->samples++;
		
	}
	rt_cl_free_kernel(&s->kernel);
	rt_cl_free(&s->info);
	SDL_DestroyTexture(s->sdl.canvas);
	SDL_DestroyRenderer(s->sdl.renderer);
	SDL_DestroyWindow(s->sdl.win);
	SDL_Quit();
	return (1);
}






