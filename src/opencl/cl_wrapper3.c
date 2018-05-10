/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_wrapper3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:56:45 by skamoza           #+#    #+#             */
/*   Updated: 2018/05/10 19:04:28 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_wrap.h"

void					rt_cl_free_kernel(t_kernel *kernel)
{
	cl_int	status;

	status = clReleaseKernel(kernel->kernel);
	check_error(status);
}

t_kernel				rt_cl_create_kernel(t_cl_info *info, char *name)
{
	cl_int		status;
	t_kernel	kernel;

	status = CL_SUCCESS;
	kernel.kernel = clCreateKernel(info->program, name, &status);
	check_error(status);
	kernel.args = 0;
	kernel.info = info;
	return (kernel);
}

void					rt_cl_push_task(t_kernel *kernel, size_t *size)
{
	cl_int status;

	status = clEnqueueNDRangeKernel(kernel->info->command_queue, kernel->kernel,
			1, NULL, size, NULL, 0, NULL, NULL);
	check_error(status);
}

void					rt_cl_join(t_cl_info *info)
{
	cl_int	status;

	status = clFlush(info->command_queue);
	check_error(status);
	status = clFinish(info->command_queue);
	check_error(status);
}

void					rt_cl_free(t_cl_info *info)
{
	cl_int	status;

	status = clReleaseProgram(info->program);
	check_error(status);
	status = clReleaseCommandQueue(info->command_queue);
	check_error(status);
	status = clReleaseContext(info->context);
	check_error(status);
}
