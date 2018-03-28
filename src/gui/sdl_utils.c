/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 14:55:53 by lberezyn          #+#    #+#             */
/*   Updated: 2018/03/28 14:55:56 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "panels.h"

// void	texture_from_text(char *text, t_sdl *sdl, t_ui_bg *p)
// {
// 	SDL_Surface	*surface;
// 	SDL_Color	color;
// 	TTF_Font	*font;

// 	TTF_Init();
// 	font = TTF_OpenFont("open-sans/OpenSans-Regular.ttf", 25);
// 	if (font == NULL)
// 		return ;
// 	color.r = 200;
// 	color.g = 200;
// 	color.b = 200;
// 	surface = TTF_RenderText_Solid(font, text, color);
// 	p->rect = sdl_rect(0, 0, surface->h / 2, surface->w / 2);
// 	p->textr = SDL_CreateTextureFromSurface(sdl->ren, surface);
// 	SDL_FreeSurface(surface);
// 	TTF_CloseFont(font);
// 	TTF_Quit();
// }

SDL_Rect	make_rect(int x, int y, int h, int w)
{
	SDL_Rect	rect;

	rect.x = x * 2;
	rect.y = y * 2;
	rect.h = h * 2;
	rect.w = w * 2;
	return (rect);
}

int			within_rect(SDL_Rect rect, int x, int y)
{
	x = x * 2;
	y = y * 2;
	if (x >= rect.x && y >= rect.y &&
			x <= rect.x + rect.w && y <= rect.y + rect.h)
		return (1);
	return (0);
}

SDL_Texture* load_texture(const char *str, t_sdl *s)
{
	SDL_Texture* texture;

	texture = IMG_LoadTexture(s->renderer, str);
	if ( texture == NULL )
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd("    -     have not been loaded to texture SDL", 2);
		return NULL;
	}
	return texture;
}