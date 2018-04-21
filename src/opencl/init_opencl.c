/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_opencl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 15:26:45 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/04/21 12:06:04 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>
#include <time.h>

void	init_opencl(t_rt *pt)
{
	cl_uint *seeds;

	seeds = (cl_uint *)malloc(MAX_WIDTH * MAX_HEIGHT * 2 * sizeof(cl_uint));
//	pt_check_error(!seeds, MALLOC_ERR, NULL);
	srand(time(0));
	rt_cl_init(&pt->info);
	rt_cl_compile(&pt->info, "./src/opencl/kernel.cl");
	pt->kernel = rt_cl_create_kernel(&pt->info, "path_tracing");
	pt->samples = 0;
	pt->job_size = pt->sdl.win_w * pt->sdl.win_h;
	for (unsigned int i = 0; i < MAX_WIDTH * MAX_HEIGHT * 2; ++i)
	{
		seeds[i] = rand();
		if (seeds[i] < 2)
			seeds[i] = 2;
	}
	pt->scene.objs_mem = 
		rt_cl_malloc_write(&pt->info, sizeof(t_object) * pt->scene.objnum, pt->scene.objs);
	pt->seeds =
		rt_cl_malloc_write(&pt->info, sizeof(cl_uint) * MAX_WIDTH * MAX_HEIGHT * 2, seeds);
	pt->colors =
		rt_cl_malloc_read(&pt->info, sizeof(cl_float3) * MAX_WIDTH * MAX_HEIGHT);
	pt->pixels_mem =
		rt_cl_malloc_read(&pt->info, sizeof(cl_int) * pt->job_size);

	clSetKernelArg(pt->kernel.kernel, 0, sizeof(cl_mem), &pt->scene.objs_mem);
	clSetKernelArg(pt->kernel.kernel, 1, sizeof(cl_uint), &pt->scene.objnum);
	clSetKernelArg(pt->kernel.kernel, 2, sizeof(t_camera), &pt->scene.camera);
	clSetKernelArg(pt->kernel.kernel, 3, sizeof(cl_mem), &pt->seeds);
	clSetKernelArg(pt->kernel.kernel, 4, sizeof(cl_mem), &pt->colors);
	clSetKernelArg(pt->kernel.kernel, 5, sizeof(cl_mem), &pt->pixels_mem);

	free(seeds);
}
