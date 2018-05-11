/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panels.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 12:00:13 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/11 15:10:09 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PANELS_H
# define FT_PANELS_H

# include "SDL.h"
# include "SDL_opengl.h"
# include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"
# include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
# include "tinyfiledialogs.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <limits.h>
# include "cl_wrap.h"
# include "rt.h"

# define BUTTON_SIZE 15
# define MAXF 2000000
# define MINF -2000000
# define SHAPE_SIZE 500
# define PROPERTIES 22

void				modify_scene(t_rt *rt, int i);
void				start_settings_win(t_rt *rt, int i);
void				remalloc_objs(t_rt *rt);
t_primitive			new_sphere(float3 origin, float radius);
t_primitive			new_plane(float3 origin, float3 normal);
t_primitive			new_cylinder(float3 origin, float3 normal,
						float radius, float height);
t_primitive			new_cone(float3 origin, float3 normal, float m1,
						float m2);
t_primitive			new_disk(float3 origin, float3 normal, float radius);
t_primitive			new_cube(float3 origin, float3 min, float3 max,
						int pipes_number);
t_primitive			new_torus(float3 origin, float3 normal,
						float small_radius2, float big_radius2);
void				add_new_cone(t_rt *rt, float3 origin);
void				add_new_cylinder(t_rt *rt, float3 origin);
void				add_new_plane(t_rt *rt, float3 origin);
void				add_new_sphere(t_rt *rt, float3 origin);
void				add_new_triangle(t_rt *rt, float3 origin);
void				add_new_cube(t_rt *rt, float3 origin);
void				add_new_torus(t_rt *rt, float3 origin);
void				add_new_disk(t_rt *rt, float3 origin);
int					this_figure_props(t_obj_type type);
void				change_value(t_rt *rt, int i, int btn);
void				apply_after_effect(t_rt *rt, int i);
void				apply_after_effect2(t_rt *rt, int i);
void 				clean_scene(t_rt *rt);
int 				this_figure_small_props(t_obj_type type);
cl_float		    my_atof(const char *val, float min, float max);
cl_uchar			my_uchar(const char *val, float min, float max);
void 				validation_fix(t_object *o);
#endif
