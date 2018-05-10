/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_wrapper2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:55:46 by skamoza           #+#    #+#             */
/*   Updated: 2018/05/10 19:04:34 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_wrap.h"

#ifdef __APPLE__
# define TYPE_CURRENT CL_DEVICE_TYPE_GPU
#else
# define TYPE_CURRENT CL_DEVICE_TYPE_CPU
#endif

void					rt_cl_init(t_cl_info *info)
{
	cl_int status;

	status = CL_SUCCESS;
	check_error(clGetPlatformIDs(1, &info->platform, &info->num_platforms));
	check_error(clGetDeviceIDs(info->platform, TYPE_CURRENT, 1,
				&info->device_id, &info->num_devices));
	status = CL_SUCCESS;
	info->context = clCreateContext(NULL, 1, &info->device_id,
			NULL, NULL, &status);
	check_error(status);
	info->command_queue = clCreateCommandQueue(info->context,
			info->device_id, 0, &status);
	check_error(status);
}

cl_mem					rt_cl_malloc_read(t_cl_info *info, size_t size)
{
	cl_int status;
	cl_mem ret;

	status = CL_SUCCESS;
	ret = clCreateBuffer(info->context, CL_MEM_READ_WRITE, size, NULL, &status);
	check_error(status);
	return (ret);
}

cl_mem					rt_cl_malloc_write(t_cl_info *info,
		size_t size, void *ptr)
{
	cl_int status;
	cl_mem ret;

	status = CL_SUCCESS;
	ret = clCreateBuffer(info->context, CL_MEM_COPY_HOST_PTR, size, ptr,
			&status);
	check_error(status);
	return (ret);
}

cl_int					rt_cl_host_to_device(t_cl_info *info, cl_mem obj,
		void *src, size_t size)
{
	cl_int status;

	status = clEnqueueWriteBuffer(info->command_queue, obj, CL_TRUE, 0, size,
			src, 0, NULL, NULL);
	check_error(status);
	return (status);
}

cl_int					rt_cl_device_to_host(t_cl_info *info, cl_mem obj,
		void *dest, size_t size)
{
	cl_int status;

	status = clEnqueueReadBuffer(info->command_queue, obj, CL_TRUE, 0, size,
			dest, 0, NULL, NULL);
	check_error(status);
	return (status);
}
