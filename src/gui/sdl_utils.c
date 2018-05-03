/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 14:55:53 by lberezyn          #+#    #+#             */
/*   Updated: 2018/04/25 12:44:19 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/panels.h"

void	texture_from_text(char *text, t_sdl *sdl, t_rec *rec)
{
	SDL_Surface	*surface;
	static const SDL_Color	color = {199, 50, 176, 0};
	TTF_Font	*font;

	TTF_Init();
	font = TTF_OpenFont("Roboto/Roboto-Light.ttf", 20);
	if (font == NULL)
		return ;
	TTF_SetFontStyle(font, TTF_STYLE_BOLD);
	surface = TTF_RenderUTF8_Blended(font, text, color);
//	surface = TTF_RenderText_Solid(font, text, color);
	rec->rect = make_rect(0, 0, surface->h / 2, surface->w / 2);
	rec->texture = SDL_CreateTextureFromSurface(sdl->renderer, surface);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	TTF_Quit();
}

void	create_canvas(t_rt *pt, int w, int h)
{
	pt->sdl.canvas = SDL_CreateTexture(
			pt->sdl.renderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_TARGET,
			w,
			h);
	rt_check_error(!pt->sdl.canvas, SDL_ERROR, (char*)SDL_GetError());
}

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
	x = x * 1;
	y = y * 1;
	if (x >= rect.x && y >= rect.y &&
			x <= rect.x + rect.w && y <= rect.y + rect.h)
		return (1);
	return (0);
}

SDL_Texture* load_texture(const char *str, t_rt *s)
{
	SDL_Texture* texture;

	texture = IMG_LoadTexture(s->sdl.renderer, str);
	if ( texture == NULL )
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd("    -     have not been loaded to texture SDL", 2);
		return NULL;
	}
	return texture;
}