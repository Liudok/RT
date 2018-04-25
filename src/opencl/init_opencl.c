/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_opencl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 15:26:45 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/04/25 12:12:26 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <time.h>

cl_uint *make_seeds(t_rt *pt)
{
	cl_uint *seeds;

	seeds = (cl_uint *)malloc(pt->sdl.win_w * pt->sdl.win_h * 2 * sizeof(cl_uint));
	pt_check_error(!seeds, MALLOC_ERR, NULL);
	pt->job_size = pt->sdl.win_w * pt->sdl.win_h;
	pt->samples = 0;
	srand(time(0));
	for (unsigned int i = 0; i < (unsigned int)(pt->sdl.win_w * pt->sdl.win_h * 2); ++i)
	{
		seeds[i] = rand();
		if (seeds[i] < 2)
			seeds[i] = 2;
	}
	return (seeds);
}

void	init_opencl(t_rt *pt)
{
	cl_uint *seeds;

	seeds = make_seeds(pt);
	rt_cl_init(&pt->info);
	rt_cl_compile(&pt->info, "./src/opencl/kernel.cl");
	pt->kernel = rt_cl_create_kernel(&pt->info, "path_tracing");
	pt->scene.objs_mem = rt_cl_malloc_write(
			&pt->info, sizeof(t_object) * pt->scene.objnum, pt->scene.objs);
	pt->seeds = rt_cl_malloc_write(
			&pt->info, sizeof(cl_uint) * pt->sdl.win_w * pt->sdl.win_h * 2, seeds);
	pt->colors = rt_cl_malloc_read(
			&pt->info, sizeof(cl_float3) * pt->sdl.win_w * pt->sdl.win_h * 2);
//	pt->textures_mem = rt_cl_create_image_tex(&pt->info, &pt->textures_img[2], 1);
	pt->pixels_mem = rt_cl_malloc_read(&pt->info, sizeof(cl_int) * pt->job_size);
	clSetKernelArg(pt->kernel.kernel, 0, sizeof(cl_mem), &pt->scene.objs_mem);
	clSetKernelArg(pt->kernel.kernel, 1, sizeof(cl_uint), &pt->scene.objnum);
	clSetKernelArg(pt->kernel.kernel, 2, sizeof(t_camera), &pt->scene.camera);
	clSetKernelArg(pt->kernel.kernel, 3, sizeof(cl_mem), &pt->seeds);
	clSetKernelArg(pt->kernel.kernel, 4, sizeof(cl_mem), &pt->colors);
	clSetKernelArg(pt->kernel.kernel, 5, sizeof(cl_mem), &pt->pixels_mem);
	clSetKernelArg(pt->kernel.kernel, 6, sizeof(cl_uint), &pt->samples);
	clSetKernelArg(pt->kernel.kernel, 7, sizeof(cl_mem), &pt->textures_mem);
	free(seeds);

}

void	reinit_opencl(t_rt *pt)
{
	cl_uint *seeds;

	seeds = make_seeds(pt);
	free(pt->scene.objs_mem);
	pt->scene.objs_mem =
			rt_cl_malloc_write(&pt->info, sizeof(t_object) * pt->scene.objnum, pt->scene.objs);
	clSetKernelArg(pt->kernel.kernel, 0, sizeof(cl_mem), &pt->scene.objs_mem);
	clSetKernelArg(pt->kernel.kernel, 1, sizeof(cl_uint), &pt->scene.objnum);
	clSetKernelArg(pt->kernel.kernel, 2, sizeof(t_camera), &pt->scene.camera);
	free(seeds);
	pt->buttons[0].pressed = 0;
}