/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 18:11:20 by skamoza           #+#    #+#             */
/*   Updated: 2018/05/11 21:41:54 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define REO STEREO

extern int g_error_flag;

typedef struct s_rt t_rt;
# include "cl_wrap.h"
# include "kernel.h"
# include <stdio.h>
# include <errno.h>
# include <time.h>

# define XSTR(s) STR(s)
# define STR(s) #s
# define SDL_ERROR "./rt: SDL Error : "
# define MALLOC_ERR "./rt: malloc allocation fails"

# define MAX_WIDTH 3840
# define MAX_HEIGHT 2160
# define WINDOW_WIDTH 1250
# define WINDOW_HEIGHT 1250
# define BUTTONS_AMOUNT 21
# define NUM_TEX 29

# include "panels.h"

typedef struct		s_event
{
	int				w : 1;
	int				s : 1;
	int				a : 1;
	int				d : 1;
	int				q : 1;
	int				e : 1;
	int				up : 1;
	int				down : 1;
	int				left : 1;
	int				right : 1;
}					t_event;

typedef struct		s_rec
{
	SDL_Rect		rect;
	SDL_Texture		*texture;
}					t_rec;

typedef struct		s_btn
{
	char			pressed;
	char			name;
	SDL_Rect		rect;
	SDL_Texture*	txt;
}					t_btn;

typedef	struct		s_scene
{
	char			*file;
	t_object		*objs;
	cl_uint 		objnum;
	t_camera		camera;
	cl_mem			objs_mem;
	t_btn			*figures;
}					t_scene;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Texture		*canvas;
	int 			win_w;
	int 			win_h;
	cl_int			*pixels;
}					t_sdl;

typedef struct		s_rt
{
	t_sdl			sdl;
	t_cl_info		info;
	t_kernel		kernel;
	t_kernel		mouse_kernel;
	t_kernel		effect_kernel;
	size_t			job_size;
	cl_mem			pixels_mem;
	cl_mem			textures_mem;
	cl_mem			tex_size_mem;
	cl_mem			colors;
	cl_mem			seeds;
	cl_uint			samples;
	cl_int			effect_type;
	cl_mem			mouse_intersect;
	t_scene			scene;
	t_event			event;
    int             painting_flag;
	SDL_Texture		*textures[NUM_TEX];
	SDL_Surface		*textures_img[NUM_TEX ];
	cl_uint2		texture_sizes[NUM_TEX + 1];
	t_btn			buttons[BUTTONS_AMOUNT];
	char			**icon;
}					t_rt;


void				ft_error(char *s);
int 				sdl_init_everything(t_rt *s);
void				init_default_scene(t_rt *rt);
SDL_Rect			make_rect(int x, int y, int h, int w);
int					within_rect(SDL_Rect rect, int x, int y);
void 				run_ui(t_rt *s);
void				set_panel(t_rt *s);
void				set_buttons(t_rt *s);
void				render_buttons(t_rt *s);
SDL_Texture*		load_texture(const char *str, t_rt *s);
void				set_bg(t_rt *s);
void				create_buttons(t_rt *s);
void				check_pressing(t_rt *s, int x, int y);
void				file_choosing(t_rt *s);
void				show_settings(t_rt *s);
void				create_new_scene(t_rt *s);
void				after_effect_panel(t_rt *s);
void 				create_figures(t_rt *s);
void				set_icons(t_rt *s);
void				create_subbuttons(t_rt *s);
void				render_subbuttons(t_rt *s);
void				load_buttons_texures(t_rt *s);
int 				load_all_textures(t_rt *s);
void				settings_rect_params(t_rec *recs);
void        		create_settings_textures(t_rt* rt, t_sdl *sdl, t_rec *recs, int i);
void				set_other_prims_fields(t_object *o, t_sdl *sdl, t_rec *recs);
void				other_prim_3_texture(t_object *o, t_sdl *sdl, t_rec *recs);
void				texture_from_text(char *text, t_sdl *sdl, t_rec *rec);
void				start_parsing(char *file_str, t_scene *s, int size);
void 				save_scene_to_file(t_rt *s);
char 				*type_to_str(int n);
void				print_prim_info(int fd, t_object *o);
void 				save_scene_to_png(t_rt *s);

void				init_sdl(t_rt *pt, int width, int height);
void				create_canvas(t_rt *pt, int w, int h);
void				init_scene(t_rt *pt);
void				init_camera(t_rt *pt, float3 origin);
void				init_opencl(t_rt *pt);
void				program_loop(t_rt *pt);
void				draw_picture(t_sdl *sdl);

float3				normalize(float3 v);
double				vlen(float3 v);
float3				vmul(float3 a, float b);
float3				vadd(float3 a, float3 b);
float3				vsub(float3 a, float3 b);
double				dot(float3 a, float3 b);
float3				cross(float3 a, float3 b);
void				create_rotation_matrix(t_rt *pt, float3 *m);
float3				vrotate(float3 v, float3 *matrix);

int					is_quit(SDL_Event e);
int					is_window_resizable(SDL_Event e);
int 				is_camera_event(t_rt *rt);
void				handling_window_resizable(t_rt *rt, SDL_Event e);
void				on_event(t_rt *rt, SDL_Event *e);
void				off_event(t_rt *rt, SDL_Event *e);
void				update_camera(t_rt *rt);
void				rotate_camera(t_rt *rt);

void				rt_check_error(int flag, char *err1, char *err2);
void				destroy(t_rt *pt);

void				reinit_opencl(t_rt *pt);
int					mouse_ray(t_rt *rt, int x, int y);
void				choosing_dialog(t_rt *rt);
void				real_values(t_object *o, t_sdl *sdl, t_rec *recs);
int					check_pressing_setting(int prop, t_rec *recs, int x, int y);
void				fill_texture(const float **ptr, t_sdl *s, t_rec *recs, cl_uint2 n);
void				real_settings_rect_params(t_rec *recs, int prop);
void				real_settings_rect_params2(t_rec *recs, int i);
void				recs_correction(t_rec *recs, t_object *o);

#endif
