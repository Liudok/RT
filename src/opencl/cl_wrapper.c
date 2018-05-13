/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_wrapper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 14:37:46 by skamoza           #+#    #+#             */
/*   Updated: 2018/05/13 15:32:59 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "cl_wrap.h"
#include "libft.h"
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

const char				*g_errors[] = { "CL_SUCCESS", "CL_DEVICE_NOT_FOUND",
	"CL_DEVICE_NOT_AVAILABLE", "CL_COMPILER_NOT_AVAILABLE",
	"CL_MEM_OBJECT_ALLOCATION_FAILURE", "CL_OUT_OF_RESOURCES",
	"CL_OUT_OF_HOST_MEMORY", "CL_PROFILING_INFO_NOT_AVAILABLE",
	"CL_MEM_COPY_OVERLAP", "CL_IMAGE_FORMAT_MISMATCH",
	"CL_IMAGE_FORMAT_NOT_SUPPORTED", "CL_BUILD_PROGRAM_FAILURE",
	"CL_MAP_FAILURE", "CL_MISALIGNED_SUB_BUFFER_OFFSET",
	"CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST",
	"CL_COMPILE_PROGRAM_FAILURE", "CL_LINKER_NOT_AVAILABLE",
	"CL_LINK_PROGRAM_FAILURE", "CL_DEVICE_PARTITION_FAILED",
	"CL_KERNEL_ARG_INFO_NOT_AVAILABLE", "CL_INVALID_VALUE",
	"CL_INVALID_DEVICE_TYPE", "CL_INVALID_PLATFORM", "CL_INVALID_DEVICE",
	"CL_INVALID_CONTEXT", "CL_INVALID_QUEUE_PROPERTIES",
	"CL_INVALID_COMMAND_QUEUE", "CL_INVALID_HOST_PTR", "CL_INVALID_MEM_OBJECT",
	"CL_INVALID_IMAGE_FORMAT_DESCRIPTOR", "CL_INVALID_IMAGE_SIZE",
	"CL_INVALID_SAMPLER", "CL_INVALID_BINARY", "CL_INVALID_BUILD_OPTIONS",
	"CL_INVALID_PROGRAM", "CL_INVALID_PROGRAM_EXECUTABLE",
	"CL_INVALID_KERNEL_NAME", "CL_INVALID_KERNEL_DEFINITION",
	"CL_INVALID_KERNEL", "CL_INVALID_ARG_INDEX", "CL_INVALID_ARG_VALUE",
	"CL_INVALID_ARG_SIZE", "CL_INVALID_KERNEL_ARGS",
	"CL_INVALID_WORK_DIMENSION", "CL_INVALID_WORK_GROUP_SIZE",
	"CL_INVALID_WORK_ITEM_SIZE", "CL_INVALID_GLOBAL_OFFSET",
	"CL_INVALID_EVENT_WAIT_LIST", "CL_INVALID_EVENT", "CL_INVALID_OPERATION",
	"CL_INVALID_GL_OBJECT", "CL_INVALID_BUFFER_SIZE", "CL_INVALID_MIP_LEVEL",
	"CL_INVALID_GLOBAL_WORK_SIZE", "CL_INVALID_PROPERTY",
	"CL_INVALID_IMAGE_DESCRIPTOR", "CL_INVALID_COMPILER_OPTIONS",
	"CL_INVALID_LINKER_OPTIONS", "CL_INVALID_DEVICE_PARTITION_COUNT"
};

const cl_image_desc		g_texture_description = {
	CL_MEM_OBJECT_IMAGE2D_ARRAY,
	2048, 1024,
	1, NUM_TEX + 2,
	0, 0, 0, 0, NULL
};

void					check_error(cl_int status)
{
	char				*error_string;

	status = -status;
	error_string = NULL;
	if (status < 20)
		error_string = (char *)g_errors[status];
	if (status <= 68)
		error_string = (char *)g_errors[status - 10];
	if (status && error_string)
	{
		ft_putendl_fd("CL_ERROR:", 2);
		ft_putendl_fd(error_string, 2);
		exit(0);
	}
}

void					rt_cl_bind_textures(t_cl_info *info, cl_mem mem,
		SDL_Surface **textures, cl_uint2 *texture_sizes)
{
	int					i;
	size_t				origin[3];
	size_t				region[3];

	i = 0;
	origin[0] = 0;
	origin[1] = 0;
	origin[2] = 0;
	region[0] = 2048;
	region[1] = 1024;
	region[2] = 1;
	check_error(clEnqueueWriteImage(info->command_queue, mem, CL_TRUE,
			origin, region, 0, 0, textures[i]->pixels, 0, NULL, NULL));
	while (i < NUM_TEX)
	{
		region[0] = textures[i]->w;
		region[1] = textures[i]->h;
		texture_sizes[i + 1].x = region[0];
		texture_sizes[i + 1].y = region[1];
		origin[2] = i + 1;
		check_error(clEnqueueWriteImage(info->command_queue, mem, CL_TRUE,
				origin, region, 0, 0, textures[i]->pixels, 0, NULL, NULL));
		i++;
	}
	origin[2] = i + 1;
}

void					rt_cl_print_debug(t_cl_info *info)
{
	size_t				log_size;
	char				*log;

	clGetProgramBuildInfo(info->program, info->device_id,
			CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
	log = (char*)malloc(log_size);
	clGetProgramBuildInfo(info->program, info->device_id,
				CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
	ft_putendl(log);
	free(log);
}

cl_int					rt_cl_compile(t_cl_info *info, char *path)
{
	int					fd;
	char				src[MAX_SOURCE_SIZE];
	size_t				size;
	cl_int				status;
	char				*seeker;

	status = CL_SUCCESS;
	if ((fd = open(path, O_RDONLY)) != -1)
	{
		size = read(fd, src, MAX_SOURCE_SIZE);
		seeker = &src[0];
		info->program = clCreateProgramWithSource(info->context, 1,
				(const char**)&seeker, (const size_t*)&size, &status);
		check_error(status);
		status = clBuildProgram(info->program, 1, &info->device_id, "-I includ"
		"es/ -I src/opencl/ -Werror -D NUM_TEX="XSTR(NUM_TEX), NULL, NULL);
		if (status)
			rt_cl_print_debug(info);
		close(fd);
	}
	else
		status = CL_BUILD_PROGRAM_FAILURE;
	check_error(status);
	return (status);
}

cl_mem					rt_cl_create_image_tex(t_cl_info *info,
		SDL_Surface **textures, cl_uint2 *texture_sizes)
{
	static const cl_image_format	fmt = {CL_RGBA, CL_UNORM_INT8};
	cl_int							status;
	cl_mem							result;

	status = CL_SUCCESS;
	result = clCreateImage(info->context, CL_MEM_READ_WRITE,
			&fmt, &g_texture_description, NULL, &status);
	check_error(status);
	rt_cl_bind_textures(info, result, textures, texture_sizes);
	return (result);
}
