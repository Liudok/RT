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
