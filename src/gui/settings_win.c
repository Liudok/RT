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

void			set_settings_bg(t_rt *s, t_sdl *sdl)
{
	SDL_Texture* bg;
	SDL_Rect backgroundPos;

	bg = s->textures[1];
	backgroundPos.x = 400;
	backgroundPos.y = 400;
	backgroundPos.w = 190;
	backgroundPos.h = 70;
	SDL_RenderCopy(sdl->renderer, bg, NULL, &backgroundPos);
	// backgroundPos.x = WINDOW_WIDTH - backgroundPos.w;
	// backgroundPos.y = 0;
	// SDL_RenderCopy(s->renderer, bg, NULL, &backgroundPos);
	SDL_RenderPresent(sdl->renderer);
//	render_buttons(s);
}
void        create_settings_textures(t_rt* rt, t_sdl *sdl, t_rec *recs, int i)
{
	printf("figure = %i\n", i);
	texture_from_text("Color RED:", sdl, &recs[0]);
	texture_from_text(ft_itoa(rt->scene.objs[i].color.s0), sdl, &recs[1]);
}
void        start_settings_win(t_rt* rt, int i)
{
    t_sdl sdl;
	int running;
	t_rec recs[10];
	running = 1;


    create_settings_win(&sdl);
	create_settings_textures(rt, &sdl, recs, i);
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
		set_settings_bg(rt, &sdl);
    }
    SDL_DestroyRenderer(sdl.renderer);
    SDL_DestroyWindow(sdl.win);
}