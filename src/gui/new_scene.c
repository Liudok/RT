/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 17:06:32 by lberezyn          #+#    #+#             */
/*   Updated: 2018/04/25 12:44:19 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/panels.h"

void				show_new_scene_panel(t_rt *s)
{
	SDL_Texture* bg;
	SDL_Rect backgroundPos;

	bg = s->textures[1];
	backgroundPos.y = 74;
	backgroundPos.w = 190;
	backgroundPos.h = 140;
	backgroundPos.x = 0;
	SDL_RenderCopy(s->sdl.renderer, bg, NULL, &backgroundPos);
	backgroundPos.y = 218;
	backgroundPos.w = 190;
	backgroundPos.h = 80;
	backgroundPos.x = 0;
	SDL_RenderCopy(s->sdl.renderer, bg, NULL, &backgroundPos);
}

void				after_effect_panel(t_rt *s)
{
	SDL_Texture* bg;
	SDL_Rect backgroundPos;
	SDL_Rect		ram;
	int				i;

	bg = s->textures[1];
	backgroundPos.y = 0;
	backgroundPos.w = 230;
	backgroundPos.h = 70;
	backgroundPos.x = 192;
	SDL_RenderCopy(s->sdl.renderer, bg, NULL, &backgroundPos);
	i = 16;
	while (i < BUTTONS_AMOUNT)
	{
		if (!s->buttons[i].pressed)
			SDL_RenderCopy(s->sdl.renderer, s->buttons[i].txt, NULL, &s->buttons[i].rect);
		else
		{
			ram.x = s->buttons[i].rect.x - 5;
			ram.y = s->buttons[i].rect.y - 5;
			ram.w = s->buttons[i].rect.w + 10;
			ram.h = s->buttons[i].rect.h + 10;
			SDL_RenderCopy(s->sdl.renderer, s->buttons[i].txt, NULL, &s->buttons[i].rect);
			SDL_RenderCopy(s->sdl.renderer, s->textures[2], NULL, &ram);
		}
		i++;
	}
}


void		create_new_scene(t_rt *s)
{

	show_new_scene_panel(s);
//	create_subbuttons(s);
//	render_subbuttons(s);
	int				i;

	i = 4;
	while (i < 16)
	{
		SDL_RenderCopy(s->sdl.renderer, s->buttons[i].txt, NULL, &s->buttons[i].rect);
		i++;
	}
}
