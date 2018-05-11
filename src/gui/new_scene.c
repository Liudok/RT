/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 17:06:32 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/11 22:51:43 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/panels.h"

void				show_new_scene_panel(t_rt *s)
{
	SDL_Texture		*bg;
	SDL_Rect		background_pos;

	bg = s->textures[1];
	background_pos.y = 74;
	background_pos.w = 190;
	background_pos.h = 140;
	background_pos.x = 0;
	SDL_RenderCopy(s->sdl.renderer, bg, NULL, &background_pos);
	background_pos.y = 218;
	background_pos.w = 190;
	background_pos.h = 80;
	background_pos.x = 0;
	SDL_RenderCopy(s->sdl.renderer, bg, NULL, &background_pos);
}

void				after_effect_panel(t_rt *s)
{
	const SDL_Texture		*bg = s->textures[1];
	SDL_Rect				background_pos;
	SDL_Rect				ram;
	int						i;

	background_pos.y = 0;
	background_pos.w = 230;
	background_pos.h = 70;
	background_pos.x = 192;
	SDL_RenderCopy(s->sdl.renderer, (SDL_Texture *)bg, NULL, &background_pos);
	i = 15;
	while (++i < BUTTONS_AMOUNT)
		if (!s->buttons[i].pressed)
			SDL_RenderCopy(s->sdl.renderer,
					s->buttons[i].txt, NULL, &s->buttons[i].rect);
		else
		{
			ram.x = s->buttons[i].rect.x - 5;
			ram.y = s->buttons[i].rect.y - 5;
			ram.w = s->buttons[i].rect.w + 10;
			ram.h = s->buttons[i].rect.h + 10;
			SDL_RenderCopy(s->sdl.renderer,
					s->buttons[i].txt, NULL, &s->buttons[i].rect);
			SDL_RenderCopy(s->sdl.renderer, s->textures[2], NULL, &ram);
		}
}

void				create_new_scene(t_rt *s)
{
	int				i;

	show_new_scene_panel(s);
	i = 4;
	while (i < 16)
	{
		SDL_RenderCopy(s->sdl.renderer, s->buttons[i].txt, NULL,
				&s->buttons[i].rect);
		i++;
	}
}
