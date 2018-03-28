/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panels.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 12:00:13 by lberezyn          #+#    #+#             */
/*   Updated: 2018/03/21 12:00:16 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PANELS_H
#define FT_PANELS_H

# include "SDL.h"
# include "SDL_opengl.h"
# include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
# include "tinyfiledialogs.h"
# include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

# define BUTTONS_AMOUNT 13
# define BUTTON_SIZE 15
# define WINDOW_WIDTH 1300
# define WINDOW_HEIGHT 1000
# define SHAPE_SIZE 500

typedef struct		s_btn
{
	char			pressed;
	char			name;
	SDL_Rect		rect;
	SDL_Texture*	txt;
}					t_btn;

typedef struct		s_sdl
{
	SDL_Window		*win;
	int 			win_w;
	int 			win_h;
	SDL_Renderer*	renderer;
	SDL_Surface*	surf;
	SDL_Texture*	texture;
	t_btn			buttons[BUTTONS_AMOUNT];
	char			*file;
	char			go;
	char **icon;
}					t_sdl;

int 			sdl_init_everything(t_sdl *s);
SDL_Rect	make_rect(int x, int y, int h, int w);
int			within_rect(SDL_Rect rect, int x, int y);
int 			run_ui(t_sdl *s);
void			set_panel(t_sdl *s);
void			set_buttons(t_sdl *s);
void			render_buttons(t_sdl *s);
SDL_Texture*	load_texture(const char *str, t_sdl *s);
void			set_bg(t_sdl *s);
void			create_buttons(t_sdl *s);
void			check_pressing(t_sdl *s, int x, int y);
void		file_choosing(t_sdl *s, int i);
void				show_settings(t_sdl *s);
void		create_new_scene(t_sdl *s);
void set_icons(t_sdl *s);
void				render_subbuttons(t_sdl *s);


#endif
