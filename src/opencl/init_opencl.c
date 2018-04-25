/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_opencl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 15:26:45 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/04/25 12:44:19 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <time.h>

static cl_uint	*make_seeds(t_rt *rt)
{
	cl_uint *seeds;

	seeds = (cl_uint *)malloc(rt->sdl.win_w * rt->sdl.win_h * 2 * sizeof(cl_uint));
	rt_check_error(!seeds, MALLOC_ERR, NULL);
	rt->job_size = rt->sdl.win_w * rt->sdl.win_h;
	rt->samples = 0;
	srand(time(0));
	for (unsigned int i = 0; i < (unsigned int)(rt->sdl.win_w * rt->sdl.win_h * 2); ++i)
	{
		seeds[i] = rand();
		if (seeds[i] < 2)
			seeds[i] = 2;
	}
	return (seeds);
}

void			init_opencl(t_rt *rt)
{
	cl_uint *seeds;

	seeds = make_seeds(rt);
	rt_cl_init(&rt->info);
	rt_cl_compile(&rt->info, "./src/opencl/kernel.cl");
	rt->kernel = rt_cl_create_kernel(&rt->info, "path_tracing");
	rt->scene.objs_mem = rt_cl_malloc_write(
			&rt->info, sizeof(t_object) * rt->scene.objnum, rt->scene.objs);
	rt->seeds = rt_cl_malloc_write(
			&rt->info, sizeof(cl_uint) * rt->sdl.win_w * rt->sdl.win_h * 2, seeds);
	rt->colors = rt_cl_malloc_read(
			&rt->info, sizeof(cl_float3) * rt->sdl.win_w * rt->sdl.win_h * 2);
	rt->textures_mem = rt_cl_create_image_tex(&rt->info, &rt->textures_img[2], 1);
	rt->pixels_mem = rt_cl_malloc_read(&rt->info, sizeof(cl_int) * rt->job_size);
	clSetKernelArg(rt->kernel.kernel, 0, sizeof(cl_mem), &rt->scene.objs_mem);
	clSetKernelArg(rt->kernel.kernel, 1, sizeof(cl_uint), &rt->scene.objnum);
	clSetKernelArg(rt->kernel.kernel, 2, sizeof(t_camera), &rt->scene.camera);
	clSetKernelArg(rt->kernel.kernel, 3, sizeof(cl_mem), &rt->seeds);
	clSetKernelArg(rt->kernel.kernel, 4, sizeof(cl_mem), &rt->colors);
	clSetKernelArg(rt->kernel.kernel, 5, sizeof(cl_mem), &rt->pixels_mem);
	clSetKernelArg(rt->kernel.kernel, 6, sizeof(cl_uint), &rt->samples);
	clSetKernelArg(rt->kernel.kernel, 7, sizeof(cl_mem), &rt->textures_mem);
	free(seeds);

}

void			reinit_opencl(t_rt *rt)
{
	cl_uint *seeds;

	seeds = make_seeds(rt);
	free(rt->scene.objs_mem);
	rt->scene.objs_mem =
			rt_cl_malloc_write(&rt->info, sizeof(t_object) * rt->scene.objnum, rt->scene.objs);
	clSetKernelArg(rt->kernel.kernel, 0, sizeof(cl_mem), &rt->scene.objs_mem);
	clSetKernelArg(rt->kernel.kernel, 1, sizeof(cl_uint), &rt->scene.objnum);
	clSetKernelArg(rt->kernel.kernel, 2, sizeof(t_camera), &rt->scene.camera);
	free(seeds);
	rt->buttons[0].pressed = 0;
}
