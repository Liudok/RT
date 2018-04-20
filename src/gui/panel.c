/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 15:07:11 by lberezyn          #+#    #+#             */
/*   Updated: 2018/04/20 20:28:00 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/panels.h"

void				show_settings(t_rt *s)
{
	SDL_Texture* bg;
	SDL_Rect backgroundPos;

	bg = s->textures[1];
	backgroundPos.y = 0;
	backgroundPos.w = 200;
	backgroundPos.h = s->sdl.win_w;
	backgroundPos.x = s->sdl.win_w - backgroundPos.w;
	SDL_RenderCopy(s->sdl.renderer, bg, NULL, &backgroundPos);
}

//void				render_subbuttons(t_sdl *s)
//{
//	int				i;
////	SDL_Texture*	rama;
////	SDL_Rect		ram;
//
//	i = 4;
////	rama = load_texture("src/img/rama.png", s);
////	rama = s->textures[2];
//	while (i < 16)
//	{
////		if (!s->buttons[i].pressed)
//			SDL_RenderCopy(s->renderer, s->buttons[i].txt, NULL, &s->buttons[i].rect);
////		else
////		{
////			if (i == 2)
////				show_settings(s);
////			ram.x = s->buttons[i].rect.x - 5;
////			ram.y = s->buttons[i].rect.y - 5;
////			ram.w = s->buttons[i].rect.w + 10;
////			ram.h = s->buttons[i].rect.h + 10;
////			SDL_RenderCopy(s->renderer, s->buttons[i].txt, NULL, &s->buttons[i].rect);
////			SDL_RenderCopy(s->renderer, rama, NULL, &ram);
////		}
//		i++;
//	}
////	SDL_DestroyTexture(rama);
//}

void				render_buttons(t_rt *s)
{
	int				i;
	SDL_Texture*	rama;
	SDL_Rect		ram;

	i = 0;
	rama = s->textures[2];
	while (i < 4)
	{
		if (!s->buttons[i].pressed)
			SDL_RenderCopy(s->sdl.renderer, s->buttons[i].txt, NULL, &s->buttons[i].rect);
		else
		{
			if (i == 2)
			{
				show_settings(s);
			}
			else if (i == 1)
				create_new_scene(s);
			ram.x = s->buttons[i].rect.x - 5;
			ram.y = s->buttons[i].rect.y - 5;
			ram.w = s->buttons[i].rect.w + 10;
			ram.h = s->buttons[i].rect.h + 10;
			SDL_RenderCopy(s->sdl.renderer, s->buttons[i].txt, NULL, &s->buttons[i].rect);
			SDL_RenderCopy(s->sdl.renderer, rama, NULL, &ram);
		}
		i++;
	}
//	SDL_DestroyTexture(rama);
	// render_subbuttons(s);
}

void			set_panel(t_rt *s)
{
	SDL_Texture* bg;
	SDL_Rect backgroundPos;

	bg = s->textures[1];
	backgroundPos.x = 0;
	backgroundPos.y = 0;
	backgroundPos.w = 190;
	backgroundPos.h = 70;
	SDL_RenderCopy(s->sdl.renderer, bg, NULL, &backgroundPos);
	// backgroundPos.x = WINDOW_WIDTH - backgroundPos.w;
	// backgroundPos.y = 0;
	// SDL_RenderCopy(s->renderer, bg, NULL, &backgroundPos);
	render_buttons(s);
}

void			set_bg(t_rt *s)
{
	SDL_Texture* bg;
	SDL_Rect backgroundPos;

	bg = s->textures[0];
	backgroundPos.x = 0;
	backgroundPos.y = 0;
	backgroundPos.w = WINDOW_WIDTH;
	backgroundPos.h = WINDOW_HEIGHT;
	SDL_RenderClear(s->sdl.renderer);
	SDL_RenderCopy(s->sdl.renderer, bg, NULL, &backgroundPos);
//	SDL_UpdateTexture(s->canvas, NULL, s->pixels, s->win_w << 2);
//	SDL_RenderCopy(s->renderer, s->canvas, NULL, NULL);
	set_panel(s);
}
