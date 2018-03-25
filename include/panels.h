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

# define BUTTONS_AMOUNT 9
# define BUTTON_SIZE 30
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
	SDL_Renderer*	renderer;
	SDL_Surface*	surf;
	t_btn			buttons[BUTTONS_AMOUNT];
	char			*file;
	char			go;
}					t_sdl;

int 			sdl_init_everything(t_sdl *s);
int 			run_ui(t_sdl *s);
void			set_panel(t_sdl *s);
void			set_buttons(t_sdl *s);
void			render_buttons(t_sdl *s);
SDL_Texture*	load_texture(const char *str, t_sdl *s);
void			set_bg(t_sdl *s);
void			create_buttons(t_sdl *s);
void			check_pressing(t_sdl *s, int x, int y);
void		file_choosing(t_sdl *s, int i);

#endif
