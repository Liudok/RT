/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_wrapper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 14:37:46 by skamoza           #+#    #+#             */
/*   Updated: 2018/03/22 13:43:55 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_wrap.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

const char *get_error_string(cl_int error)
{
	switch(error) {
		// run-time and JIT compiler errors
		case 0: return "CL_SUCCESS";
		case -1: return "CL_DEVICE_NOT_FOUND";
		case -2: return "CL_DEVICE_NOT_AVAILABLE";
		case -3: return "CL_COMPILER_NOT_AVAILABLE";
		case -4: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
		case -5: return "CL_OUT_OF_RESOURCES";
		case -6: return "CL_OUT_OF_HOST_MEMORY";
		case -7: return "CL_PROFILING_INFO_NOT_AVAILABLE";
		case -8: return "CL_MEM_COPY_OVERLAP";
		case -9: return "CL_IMAGE_FORMAT_MISMATCH";
		case -10: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
		case -11: return "CL_BUILD_PROGRAM_FAILURE";
		case -12: return "CL_MAP_FAILURE";
		case -13: return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
		case -14: return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
		case -15: return "CL_COMPILE_PROGRAM_FAILURE";
		case -16: return "CL_LINKER_NOT_AVAILABLE";
		case -17: return "CL_LINK_PROGRAM_FAILURE";
		case -18: return "CL_DEVICE_PARTITION_FAILED";
		case -19: return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";

				  // compile-time errors
		case -30: return "CL_INVALID_VALUE";
		case -31: return "CL_INVALID_DEVICE_TYPE";
		case -32: return "CL_INVALID_PLATFORM";
		case -33: return "CL_INVALID_DEVICE";
		case -34: return "CL_INVALID_CONTEXT";
		case -35: return "CL_INVALID_QUEUE_PROPERTIES";
		case -36: return "CL_INVALID_COMMAND_QUEUE";
		case -37: return "CL_INVALID_HOST_PTR";
		case -38: return "CL_INVALID_MEM_OBJECT";
		case -39: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
		case -40: return "CL_INVALID_IMAGE_SIZE";
		case -41: return "CL_INVALID_SAMPLER";
		case -42: return "CL_INVALID_BINARY";
		case -43: return "CL_INVALID_BUILD_OPTIONS";
		case -44: return "CL_INVALID_PROGRAM";
		case -45: return "CL_INVALID_PROGRAM_EXECUTABLE";
		case -46: return "CL_INVALID_KERNEL_NAME";
		case -47: return "CL_INVALID_KERNEL_DEFINITION";
		case -48: return "CL_INVALID_KERNEL";
		case -49: return "CL_INVALID_ARG_INDEX";
		case -50: return "CL_INVALID_ARG_VALUE";
		case -51: return "CL_INVALID_ARG_SIZE";
		case -52: return "CL_INVALID_KERNEL_ARGS";
		case -53: return "CL_INVALID_WORK_DIMENSION";
		case -54: return "CL_INVALID_WORK_GROUP_SIZE";
		case -55: return "CL_INVALID_WORK_ITEM_SIZE";
		case -56: return "CL_INVALID_GLOBAL_OFFSET";
		case -57: return "CL_INVALID_EVENT_WAIT_LIST";
		case -58: return "CL_INVALID_EVENT";
		case -59: return "CL_INVALID_OPERATION";
		case -60: return "CL_INVALID_GL_OBJECT";
		case -61: return "CL_INVALID_BUFFER_SIZE";
		case -62: return "CL_INVALID_MIP_LEVEL";
		case -63: return "CL_INVALID_GLOBAL_WORK_SIZE";
		case -64: return "CL_INVALID_PROPERTY";
		case -65: return "CL_INVALID_IMAGE_DESCRIPTOR";
		case -66: return "CL_INVALID_COMPILER_OPTIONS";
		case -67: return "CL_INVALID_LINKER_OPTIONS";
		case -68: return "CL_INVALID_DEVICE_PARTITION_COUNT";
	
	}
	return "";
}

void		check_error(cl_int status)
{
	if (status != CL_SUCCESS)
	{
		printf("CL_ERROR %s\n", get_error_string(status));
		exit(0);
	}

}
void		rt_cl_init(t_cl_info *info)
{
	cl_int		status;

	status = CL_SUCCESS;
	check_error(clGetPlatformIDs(
				1, &info->platform,
				&info->num_platforms));
	check_error(clGetDeviceIDs(
				info->platform,
				CL_DEVICE_TYPE_GPU,
		//		CL_DEVICE_TYPE_CPU,
				1, &info->device_id,
				&info->num_devices));
	status = CL_SUCCESS;
	info->context = clCreateContext(
				NULL, 1,
				&info->device_id,
				NULL, NULL,
				&status);
	check_error(status);
	info->command_queue = clCreateCommandQueue(
				info->context,
				info->device_id,
				0,
				&status);
	check_error(status);
}

cl_mem		rt_cl_malloc_read(t_cl_info *info, size_t size)
{
	cl_int		status;
	cl_mem		ret;

	status = CL_SUCCESS;
	ret = clCreateBuffer(
				info->context,
				CL_MEM_READ_WRITE,
				size,
				NULL,
				&status);
    check_error(status);
	return (ret);
}

cl_mem		rt_cl_malloc_write(t_cl_info *info, size_t size, void *ptr)
{
	cl_int		status;
	
	status = CL_SUCCESS;
	cl_mem		ret;
	ret = clCreateBuffer(
				info->context,
				CL_MEM_COPY_HOST_PTR,
				size,
				ptr,
				&status);
    check_error(status);
	return (ret);
}

cl_int		rt_cl_host_to_device(
		t_cl_info *info,
		cl_mem obj,
		void *src,
		size_t size)
{
	cl_int		status;

	status = clEnqueueWriteBuffer(
				info->command_queue,
				obj,
				CL_TRUE,
				0,
				size,
				src,
				0,
				NULL,
				NULL);
	check_error(status);
	return (status);
}

cl_int		rt_cl_device_to_host(
		t_cl_info *info,
		cl_mem obj,
		void *dest,
		size_t size)
{
	cl_int		status;

	status = clEnqueueReadBuffer(
				info->command_queue,
				obj,
				CL_TRUE,
				0,
				size,
				dest,
				0,
				NULL,
				NULL);
	check_error(status);
	return (status);
}

cl_int		rt_cl_compile(t_cl_info *info, char *path)
{
	int		fd;
	char	src[MAX_SOURCE_SIZE];
	size_t	size;
	cl_int	status;
	char	*seeker;

	status = CL_SUCCESS;
//	printf("path: %s\n", path);
	if ((fd = open(path, O_RDONLY)) != -1)
	{
		size = read(fd, src, MAX_SOURCE_SIZE);
		seeker = &src[0];
		info->program = clCreateProgramWithSource(
				info->context, 1,
				(const char **)&seeker,
				(const size_t *)&size,
				&status);
		check_error(status);
		status = clBuildProgram(info->program,
				1, &info->device_id, "-I inc/", NULL, NULL);
		if (status != 0) {
			printf("status = %i\n", status);
			// Determine the size of the log
			size_t log_size;
			clGetProgramBuildInfo(info->program, info->device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

			// Allocate memory for the log
			char *log = (char *) malloc(log_size);

			// Get the log
			clGetProgramBuildInfo(info->program, info->device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

			// Print the log
			printf("log: %s\n", log);
		}

		close(fd);
	}
	else
		status = CL_BUILD_PROGRAM_FAILURE;
	check_error(status);
	return (status);
}

void		rt_cl_join(t_cl_info *info)
{
	cl_int		status;

	status = clFlush(info->command_queue);
	check_error(status);
	status = clFinish(info->command_queue);
	check_error(status);
}

void		rt_cl_free(t_cl_info *info)
{
	cl_int		status;

	status = clReleaseProgram(info->program);
	check_error(status);
	status = clReleaseCommandQueue(info->command_queue);
	check_error(status);
	status = clReleaseContext(info->context);
	check_error(status);
}
//off_t asd


void		rt_cl_free_kernel(t_kernel *kernel)
{
	cl_int		status;

	status = clReleaseKernel(kernel->kernel);
	check_error(status);
}

t_kernel	rt_cl_create_kernel(t_cl_info *info, char *name)
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

void		rt_cl_push_arg(t_kernel *kernel, void *src, size_t size)
{
	cl_int		status;

	status = clSetKernelArg(kernel->kernel, kernel->args++, size, src);
	check_error(status);
}

void		rt_cl_drop_arg(t_kernel *kernel)
{
	kernel->args = 0;
}

void		rt_cl_push_task(t_kernel *kernel, size_t *size)
{
	cl_int		status;

	status = clEnqueueNDRangeKernel(kernel->info->command_queue,
			kernel->kernel, 1,
			NULL, size, NULL, 0, NULL, NULL);
	check_error(status);
}
