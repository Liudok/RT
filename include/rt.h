/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 18:11:20 by skamoza           #+#    #+#             */
/*   Updated: 2018/04/25 12:30:37 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <stdio.h>
# include <errno.h>
# include "panels.h"
# include "kernel.h"

# define SDL_ERROR "./RT: SDL Error : "
# define MALLOC_ERR "./rt: malloc allocation fails"

# define MAX_WIDTH 1000
# define MAX_HEIGHT 1000
# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 1000
# define BUTTONS_AMOUNT 16

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
	size_t			job_size;
	cl_mem			pixels_mem;
	cl_mem			textures_mem;
	cl_mem			colors;
	cl_mem			seeds;
	cl_uint			samples;
	t_scene			scene;
	t_event			event;

	SDL_Texture		*textures[3];
	SDL_Surface		*textures_img[3];
	t_btn			buttons[BUTTONS_AMOUNT];
	char			**icon;
}					t_rt;


void				ft_error(char *s);
int 				sdl_init_everything(t_rt *s);
void				init_default_scene(t_rt *rt);
SDL_Rect			make_rect(int x, int y, int h, int w);
int					within_rect(SDL_Rect rect, int x, int y);
int 				run_ui(t_rt *s);
void				set_panel(t_rt *s);
void				set_buttons(t_rt *s);
void				render_buttons(t_rt *s);
SDL_Texture*		load_texture(const char *str, t_rt *s);
void				set_bg(t_rt *s);
void				create_buttons(t_rt *s);
void				check_pressing(t_rt *s, int x, int y);
void				file_choosing(t_rt *s, int i);
void				show_settings(t_rt *s);
void				create_new_scene(t_rt *s);
void				set_icons(t_rt *s);
void				create_subbuttons(t_rt *s);
void				render_subbuttons(t_rt *s);
void				load_buttons_texures(t_rt *s);
int 				load_all_textures(t_rt *s);
void				start_parsing(char			*file_str, t_scene *s, int size);
void 				save_scene_to_file(t_rt *s);
char 				*type_to_str(int n);
void				print_prim_info(int fd, t_object *o, int i);
void				print_prim_info2(int fd, t_object *o, int i);
void 				save_scene_to_png(t_rt *s);

void				init_sdl(t_rt *pt, int width, int height);
void				create_texture(t_rt *pt, int w, int h);
void				init_scene(t_rt *pt);
void				init_camera(t_rt *pt);
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
void				createRotationMatrix(t_rt *pt, float3 *m);
float3				vrotate(float3 v, float3 *matrix);

int					isQuit(SDL_Event e);
int					isWindowResizable(SDL_Event e);
void				handlingWindowResizable(t_rt *pt, SDL_Event e);
void				onEvent(t_rt *pt, SDL_Event *e);
void				offEvent(t_rt *pt, SDL_Event *e);
int 				isCameraEvent(t_rt *pt);
void				updateCamera(t_rt *pt);
void				rotateCamera(t_rt *pt);

void				pt_check_error(int flag, char *err1, char *err2);
void				destroy(t_rt *pt);

void				reinit_opencl(t_rt *pt);

#endif
