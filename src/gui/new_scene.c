/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 17:06:32 by lberezyn          #+#    #+#             */
/*   Updated: 2018/03/28 17:06:35 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "panels.h"

void			create_subbuttons(t_sdl *s)
{
	int i;
	int k;

	i = 4;
	k = 0;
	while (i < 12)
	{
		s->buttons[i].pressed = 0;
		s->buttons[i].name = i;
		if (i < 8)
			s->buttons[i].rect = make_rect((10 + k * 20), 50, BUTTON_SIZE, BUTTON_SIZE);
		else if (i < 12)
			s->buttons[i].rect = make_rect((10 + k * 20), 80, BUTTON_SIZE, BUTTON_SIZE);
		s->buttons[i].txt = load_texture(s->icon[i], s);
		i++;
		k++;
		if (i >= 8 && k == 4)
			k = 0;
	}
}


void				show_new_scene_panel(t_sdl *s)
{
	SDL_Texture* bg;
	SDL_Rect backgroundPos;

	bg = load_texture("src/img/dark_pixel.png", s);
	backgroundPos.y = 82;
	backgroundPos.w = 190;
	backgroundPos.h = 140;
	backgroundPos.x = 0;
	SDL_RenderCopy(s->renderer, bg, NULL, &backgroundPos);
	backgroundPos.y = 252;
	backgroundPos.w = 190;
	backgroundPos.h = 80;
	backgroundPos.x = 0;
	SDL_RenderCopy(s->renderer, bg, NULL, &backgroundPos);
}



void		create_new_scene(t_sdl *s)
{

	show_new_scene_panel(s);
	create_subbuttons(s);
	render_subbuttons(s);

}
