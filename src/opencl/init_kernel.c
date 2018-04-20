/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_kernel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:11:28 by lberezyn          #+#    #+#             */
/*   Updated: 2018/04/20 20:26:59 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "time.h"

int init_kernel(t_rt *s)
{
	size_t			job_size = s->sdl.win_w * s->sdl.win_h;
//	t_kernel	 	size;
//	t_scene			scene;
	cl_int			pixels[job_size];

	bzero(pixels, sizeof(pixels));
	s->sdl.pixels = pixels;
	rt_cl_init(&s->info);
	rt_cl_compile(&s->info, "kernel.cl");

//	size = rt_cl_create_kernel(&s->info, "t_hit_size");
//	s->primary = rt_cl_create_kernel(&s->info, "first_intersection");
//	s->extended = rt_cl_create_kernel(&s->info, "path_tracing");
//	s->smooth = rt_cl_create_kernel(&s->info, "smooth");

//	cl_mem	hits = rt_cl_malloc_read(&s->info, 144 * job_size);
//	cl_mem	buff = rt_cl_malloc_read(&s->info, sizeof(cl_int) * job_size);
//	s->out = rt_cl_malloc_read(&s->info, sizeof(cl_int) * job_size);
//
//	clSetKernelArg(s->primary.kernel, 0, sizeof(cl_mem), &hits);
//	//ret = clSetKernelArg(extended.kernel, 0, sizeof(t_scene), &scene);
//	clSetKernelArg(s->extended.kernel, 0, sizeof(cl_mem), &hits);
//	clSetKernelArg(s->extended.kernel, 1, sizeof(cl_mem), &buff);
//	clSetKernelArg(s->smooth.kernel, 0, sizeof(cl_mem), &buff);
//	clSetKernelArg(s->smooth.kernel, 1, sizeof(cl_mem), &s->out);
//
//	rt_cl_push_task(&s->primary, &job_size);
//	rt_cl_push_task(&s->extended, &job_size);
//	rt_cl_push_task(&s->extended, &job_size);
//	rt_cl_push_task(&s->extended, &job_size);
	cl_uint seeds[s->sdl.win_w * s->sdl.win_h * 2];
	srand(time(0));
	s->kernel = rt_cl_create_kernel(&s->info, "path_tracing");
	for (unsigned int i = 0; i < job_size * 2; ++i)
	{
		seeds[i] = rand();
		if (seeds[i] < 2)
			seeds[i] = 2;
	}
	s->seeds = rt_cl_malloc_write(&s->info, sizeof(cl_uint) * job_size * 2, seeds);
	s->colors = rt_cl_malloc_read(&s->info, sizeof(cl_float3) * job_size);
	s->pixels_mem = rt_cl_malloc_write(&s->info, sizeof(cl_int) * job_size, s->sdl.pixels);
//	s->samples = 0;
	clSetKernelArg(s->kernel.kernel, 0, sizeof(cl_mem), &s->seeds);
	clSetKernelArg(s->kernel.kernel, 1, sizeof(cl_mem), &s->colors);
	clSetKernelArg(s->kernel.kernel, 2, sizeof(cl_mem), &s->pixels_mem);

//			rt_cl_join(&s->info);

//	bzero(pixels, sizeof(pixels));
//	while (1)
//	{
//		if (SDL_PollEvent(&event) && (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)))
//			break ;
//		for (int i = 0; i < 2; i++)
//			rt_cl_push_task(&extended, &job_size);
//		rt_cl_push_task(&smooth, &job_size);
//		rt_cl_device_to_host(&info, out, pixels, job_size * sizeof(int));
//		rt_cl_join(&info);
//		//smooth(pixels, width, height);
//		SDL_UpdateTexture(canvas, NULL, pixels, width << 2);
//		//SDL_RenderClear(renderer);
//		SDL_RenderCopy(renderer, canvas, NULL, NULL);
//		SDL_RenderPresent(renderer);
//	}
//	SDL_DestroyTexture(canvas);
//	SDL_DestroyRenderer(renderer);
//	SDL_DestroyWindow(window);
//	rt_cl_free_kernel(&primary);
//	rt_cl_free_kernel(&extended);
//	rt_cl_free_kernel(&size);
//	rt_cl_free(&info);
//	clReleaseMemObject(hits);
//	clReleaseMemObject(buff);
//	SDL_Quit();
	return (0);
}
