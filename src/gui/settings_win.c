/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_win.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:51:45 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/01 18:51:49 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/panels.h"

void        create_settings_win(t_sdl *sdl)
{
//    t_sdl *sdl = NULL;
//	printf("figure = %i\n", i);
    sdl->win = SDL_CreateWindow("Settings",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               400, 500,
                               SDL_WINDOW_RESIZABLE);
    sdl->renderer = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_ACCELERATED);
    sdl->canvas = SDL_CreateTexture(sdl->renderer,
                                  SDL_PIXELFORMAT_ARGB8888,
                                  SDL_TEXTUREACCESS_TARGET,
                                  400, 500);
    SDL_SetRenderDrawColor(sdl->renderer, 0, 255, 0, 255);
}


void        start_settings_win(t_rt* rt, int i)
{
    t_sdl sdl;
	int running;

	running = 1;
	printf("figure = %i\n", i);

    create_settings_win(&sdl);
    SDL_Event evt;
    while (running)
    {
        while (SDL_PollEvent(&evt))
        {
            if (is_quit(evt))
                running = 0;
            else if (evt.type == SDL_KEYDOWN)
                on_event(rt, &evt);
            else if (evt.type == SDL_KEYUP)
                off_event(rt, &evt);
            else if (evt.type == SDL_MOUSEBUTTONDOWN)
            {
//                check_pressing(s, evt.button.x, evt.button.y);
//                render_buttons(s);
//                fig = mouse_ray(s, evt.button.x, evt.button.y);
//                if (fig > 0) {
//                    printf("figure2 = %i\n", fig);
//                    start_settings_win(s, fig);
//                }
            }
        }
    }
    SDL_DestroyRenderer(sdl.renderer);
    SDL_DestroyWindow(sdl.win);
}