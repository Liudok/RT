/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 15:07:11 by lberezyn          #+#    #+#             */
/*   Updated: 2018/03/20 15:07:14 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/panels.h"

void				show_settings(t_sdl *s)
{
	SDL_Texture* bg;
	SDL_Rect backgroundPos;

//	bg = load_texture("src/img/dark_pixel.png", s);
	bg = s->textures[1];
	backgroundPos.y = 0;
	backgroundPos.w = 200;
	backgroundPos.h = s->win_w;
	backgroundPos.x = s->win_w - backgroundPos.w;
	SDL_RenderCopy(s->renderer, bg, NULL, &backgroundPos);
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

void				render_buttons(t_sdl *s)
{
	int				i;
	SDL_Texture*	rama;
	SDL_Rect		ram;

	i = 0;
	rama = s->textures[2];
	while (i < 4)
	{
		if (!s->buttons[i].pressed)
			SDL_RenderCopy(s->renderer, s->buttons[i].txt, NULL, &s->buttons[i].rect);
		else
		{
			if (i == 2)
			{
				printf("Ya staraius!");
				show_settings(s);
			}
			else if (i == 1)
				create_new_scene(s);
			ram.x = s->buttons[i].rect.x - 5;
			ram.y = s->buttons[i].rect.y - 5;
			ram.w = s->buttons[i].rect.w + 10;
			ram.h = s->buttons[i].rect.h + 10;
			SDL_RenderCopy(s->renderer, s->buttons[i].txt, NULL, &s->buttons[i].rect);
			SDL_RenderCopy(s->renderer, rama, NULL, &ram);
		}
		i++;
	}
//	SDL_DestroyTexture(rama);
	// render_subbuttons(s);
}

void			set_panel(t_sdl *s)
{
	SDL_Texture* bg;
	SDL_Rect backgroundPos;

//	bg = load_texture("src/img/dark_pixel.png", s);
	bg = s->textures[1];
	backgroundPos.x = 0;
	backgroundPos.y = 0;
	backgroundPos.w = 190;
	backgroundPos.h = 70;
	SDL_RenderCopy(s->renderer, bg, NULL, &backgroundPos);
	// backgroundPos.x = WINDOW_WIDTH - backgroundPos.w;
	// backgroundPos.y = 0;
	// SDL_RenderCopy(s->renderer, bg, NULL, &backgroundPos);
	render_buttons(s);
}

void			set_bg(t_sdl *s)
{
	SDL_Texture* bg;
	SDL_Rect backgroundPos;
//
//	bg = load_texture("src/img/dark_pixel2.png", s);
	bg = s->textures[0];
	backgroundPos.x = 0;
	backgroundPos.y = 0;
	backgroundPos.w = WINDOW_WIDTH;
	backgroundPos.h = WINDOW_HEIGHT;
	SDL_RenderClear(s->renderer);
	SDL_RenderCopy(s->renderer, bg, NULL, &backgroundPos);
//	SDL_UpdateTexture(s->canvas, NULL, s->pixels, s->win_w << 2);
//	SDL_RenderCopy(s->renderer, s->canvas, NULL, NULL);
	set_panel(s);
}

// void			set_panels(SDL_Renderer* renderer, SDL_Surface* screenSurface)
// {
// 	SDL_Texture* txt = NULL;
// 	SDL_Rect SrcR;
// 	SDL_Rect DestR;

// 	SrcR.x = 0;
// 	SrcR.y = 0;
// 	SrcR.w = 300;
// 	SrcR.h = WINDOW_HEIGHT;

// 	DestR.x = 0;
// 	DestR.y = 0;
// 	DestR.w = 400;
// 	DestR.h = WINDOW_HEIGHT;

// 	screenSurface = SDL_CreateRGBSurface(0, DestR.w, DestR.h, 32, 0, 0, 0, 0);
// 	SDL_SetRenderDrawColor( renderer, 48, 214, 250, 255 );
// 	// SDL_RenderClear( renderer );
// 	// SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
// 	SDL_RenderDrawRect( renderer, &DestR);
// 	// SDL_FillRect(screenSurface, &DestR, SDL_MapRGB(screenSurface->format, 255, 0, 0));
// 	// txt = SDL_CreateTextureFromSurface(renderer, screenSurface);
// 	// SDL_FreeSurface(screenSurface);
// 	// SDL_RenderCopy(renderer, txt, &SrcR, &DestR);
// 	// SDL_RenderPresent(renderer);
// }