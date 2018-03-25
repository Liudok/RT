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

#include "panels.h"

void				render_buttons(t_sdl *s)
{
	int				i;
	SDL_Texture*	rama;
	SDL_Rect		ram;

	i = 0;
	rama = load_texture("src/img/pressed2.png", s);
	while (i < BUTTONS_AMOUNT)
	{
		if (!s->buttons[i].pressed)
		{
			SDL_RenderCopy(s->renderer, s->buttons[i].txt, NULL, &s->buttons[i].rect);
		}
		else
		{
			// printf("pressed i = %i\n", i);
			ram.x = s->buttons[i].rect.x - 5;
			ram.y = s->buttons[i].rect.y - 5;
			ram.w = s->buttons[i].rect.w + 10;
			ram.h = s->buttons[i].rect.h + 10;
			SDL_RenderCopy(s->renderer, s->buttons[i].txt, NULL, &s->buttons[i].rect);
			SDL_RenderCopy(s->renderer, rama, NULL, &ram);
		}
		// if (i == 8)
		// {
			
		// }
		i++;
	}
	SDL_DestroyTexture(rama);
}

void			set_panel(t_sdl *s)
{
	SDL_Texture* bg;
	SDL_Rect backgroundPos;

	bg = load_texture("src/img/pixel.png", s);
	backgroundPos.x = 0;
	backgroundPos.y = 0;
	backgroundPos.w = 200;
	backgroundPos.h = WINDOW_HEIGHT;
	SDL_RenderCopy(s->renderer, bg, NULL, &backgroundPos);
	backgroundPos.x = WINDOW_WIDTH - backgroundPos.w;
	backgroundPos.y = 0;
	SDL_RenderCopy(s->renderer, bg, NULL, &backgroundPos);
	render_buttons(s);
}

void			set_bg(t_sdl *s)
{
	SDL_Texture* bg;
	SDL_Rect backgroundPos;

	bg = load_texture("src/img/pixel4.png", s);
	backgroundPos.x = 0;
	backgroundPos.y = 0;
	backgroundPos.w = WINDOW_WIDTH;
	backgroundPos.h = WINDOW_HEIGHT;
	SDL_RenderClear(s->renderer);
	SDL_RenderCopy(s->renderer, bg, NULL, &backgroundPos);
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