/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_wrap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 17:34:10 by skamoza           #+#    #+#             */
/*   Updated: 2018/05/03 16:58:29 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_WRAP_H
# define CL_WRAP_H

# define MAX_SOURCE_SIZE (0x100000)
# define CL_USE_DEPRECATED_OPENCL_1_2_APIS
# include "SDL.h"

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

typedef unsigned char	t_byte;

typedef struct			s_cl_info
{
	cl_uint				num_devices;
	cl_uint				num_platforms;
	cl_device_id		device_id;
	cl_command_queue	command_queue;
	cl_context			context;
	cl_program			program;
	cl_platform_id		platform;
}						t_cl_info;

typedef struct			s_kernel
{
	t_cl_info			*info;
	cl_kernel			kernel;
	cl_uint				args;
}						t_kernel;

/*
** Funcion to initialize the struct, getting the platform, devices,
** context and command queue.
*/
void			rt_cl_init(t_cl_info *info);

/*
** Creating read-only buffer.
*/
cl_mem			rt_cl_malloc_read(t_cl_info *info, size_t size);

/*
** Creating write-only buffer.
*/
cl_mem			rt_cl_malloc_write(t_cl_info *info, size_t size, void *ptr);

/*
** Writing data to devices' memory.
*/
cl_int			rt_cl_host_to_device(
							t_cl_info *info,
							cl_mem obj,
							void *src,
							size_t size);

/*
** Reading data from devices' memory.
*/
cl_int			rt_cl_device_to_host(
							t_cl_info *info,
							cl_mem obj,
							void *dest,
							size_t size);

/*
** Compiling the program from source.
*/
cl_int			rt_cl_compile(t_cl_info *info, char *path);

/*
** Waiting for every task in queue to complete.
*/
void			rt_cl_join(t_cl_info *info);

/*
** Destruction of program, command_queue and context.
*/
void			rt_cl_free(t_cl_info *info);

/*
** Destruction of kernel.
*/
void		rt_cl_free_kernel(t_kernel *kernel);

/*
** Creating a kernel.
*/
t_kernel		rt_cl_create_kernel(t_cl_info *info, char *name);

/*
** Pushing the next argument to the kernel.
*/
void			rt_cl_push_arg(t_kernel *kernel, void *src, size_t size);

/*
** Forget the old args.
*/
void			rt_cl_drop_arg(t_kernel *kernel);

/*
** Start working with "size" number of threads.
*/
void			rt_cl_push_task(t_kernel *kernel, size_t *size);

cl_mem			rt_cl_create_image(t_cl_info *info, cl_int2);

cl_mem			rt_cl_create_image_tex(t_cl_info *info,
					SDL_Surface **textures, cl_uint2 *);

void			rt_cl_bind_textures(t_cl_info *info, cl_mem mem,
					SDL_Surface **textures, cl_uint2 *);
#endif
