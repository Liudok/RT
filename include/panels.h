/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panels.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 12:00:13 by lberezyn          #+#    #+#             */
/*   Updated: 2018/04/26 13:35:09 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PANELS_H
#define FT_PANELS_H

# include "SDL.h"
# include "SDL_opengl.h"
# include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"
# include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
# include "tinyfiledialogs.h"
# include "../libft/libft.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
# include "cl_wrap.h"
# include "rt.h"

# define BUTTON_SIZE 15
# define SHAPE_SIZE 500
# define PROPERTIES 22

void        		modify_scene(t_rt *rt, int i);
void        		start_settings_win(t_rt* rt, int i);
t_primitive			new_sphere(float3 origin, float radius);
t_primitive			new_plane(float3 origin, float3 normal);
t_primitive			new_cylinder(float3 origin, float3 normal, float radius, float height);
t_primitive			new_cone(float3 origin, float3 normal, float m1, float m2);
t_primitive			new_disk(float3 origin, float3 normal, float radius);
void				add_new_cone(t_rt *rt, float3 origin);
void				add_new_cylinder(t_rt *rt, float3 origin);
void				add_new_plane(t_rt *rt, float3 origin);
void				add_new_sphere(t_rt *rt, float3 origin);
void				add_new_triangle(t_rt *rt, float3 origin);
int 				this_figure_props(t_obj_type type);

#endif
