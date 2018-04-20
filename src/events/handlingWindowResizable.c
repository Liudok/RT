/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlingWindowResizable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 16:13:53 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/04/19 16:13:55 by ftymchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pt.h"

void	handlingWindowResizable(t_pt *pt, SDL_Event e)
{
	pt->sdl.width = (e.window.data1 > MAX_WIDTH) ? MAX_WIDTH : e.window.data1;
	pt->sdl.height = (e.window.data2 > MAX_HEIGHT) ? MAX_HEIGHT : e.window.data2;
	SDL_DestroyTexture(pt->sdl.canvas);
	clReleaseMemObject(pt->pixels);
	free(pt->sdl.pixels);
	pt->samples = 0;
	pt->job_size = pt->sdl.width * pt->sdl.height;
	create_texture(pt, pt->sdl.width, pt->sdl.height);
	pt->sdl.pixels =
		(int*)malloc(sizeof(int) * pt->job_size);
	pt_check_error(!pt->sdl.pixels, MALLOC_ERR, NULL);
	pt->pixels =
		rt_cl_malloc_read(&pt->cl_info, sizeof(cl_int) * pt->job_size);
	init_camera(pt->scene.camera.origin, pt);
	rotateCamera(pt);
	clSetKernelArg(pt->kernel.kernel, 2, sizeof(t_camera), &pt->scene.camera);
	clSetKernelArg(pt->kernel.kernel, 5, sizeof(cl_mem), &pt->pixels);
}

