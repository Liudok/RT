/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlingWindowResizable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 16:13:53 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/04/24 16:46:38 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	handlingWindowResizable(t_rt *pt, SDL_Event e)
{
	pt->sdl.win_w = (e.window.data1 > MAX_WIDTH) ? MAX_WIDTH : e.window.data1;
	pt->sdl.win_h = (e.window.data2 > MAX_HEIGHT) ? MAX_HEIGHT : e.window.data2;
	SDL_DestroyTexture(pt->sdl.canvas);
	clReleaseMemObject(pt->pixels_mem);
	free(pt->sdl.pixels);
	pt->samples = 0;
	pt->job_size = pt->sdl.win_w * pt->sdl.win_h;
	create_texture(pt, pt->sdl.win_w, pt->sdl.win_h);
	pt->sdl.pixels =
		(int*)malloc(sizeof(int) * pt->job_size);
	// pt_check_error(!pt->sdl.pixels, MALLOC_ERR, NULL);
	pt->pixels_mem =
		rt_cl_malloc_read(&pt->info, sizeof(cl_int) * pt->job_size);
	init_camera(pt);
	rotateCamera(pt);
	clSetKernelArg(pt->kernel.kernel, 2, sizeof(t_camera), &pt->scene.camera);
	clSetKernelArg(pt->kernel.kernel, 5, sizeof(cl_mem), &pt->pixels_mem);
}

