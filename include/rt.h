/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 18:11:20 by skamoza           #+#    #+#             */
/*   Updated: 2018/03/22 16:59:34 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <stdio.h>
# include <math.h>
# include <errno.h>
# include "panels.h"
# include "cl_wrap.h"
# include "mac_key.h"
# include "parser.h"
# include "libft.h"
# include "SDL.h"

// # define MES1 "Usage : ./RTv1 scene_number(1-8)"
// # define MES2 "File opening failed"
// # define MES3 "Reading failure"
// # define MES4 "Memory allocation failure"
# define MES5 "Invalid scene file"

typedef	cl_double3    t_vec;

union				u_color
{
	unsigned int	color;
	unsigned char	channels[4];
};

enum		e_light {
	ambient,
	point,
	end_light
};

enum
{
	light,
	sphere,
	plane,
	cylinder,
	cone,
};

typedef struct		s_obj
{
	short			type;
	double			rad;
	t_vec			rot;
	t_vec			pos;
	union u_color	col;
	double			alpha;
}					t_obj;

typedef struct	s_camera
{
	cl_double3	origin;
	cl_double3	dir;
	cl_double3	viewport;
	cl_int2		canvas;
}				t_camera;

typedef struct	s_scene
{
	t_camera	camera;
	t_obj		*objs;
	cl_mem		objects;
	cl_int		objects_num;
}				t_scene;

void				ft_error(char *s);
void				ft_cr_sphere(t_obj *s, cl_uchar4 col,
									t_vec pos, cl_double rad);
void				ft_cr_plane(t_obj *s, cl_uchar4 col,
								t_vec pos, t_vec rot);
void				ft_cr_cyl(t_obj *s, cl_uchar4 col,
								t_vec pos, t_vec rot);
void				ft_cr_cone(t_obj *s, cl_uchar4 col,
								t_vec pos, t_vec rot);

#endif
