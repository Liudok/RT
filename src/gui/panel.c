/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 15:07:11 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/02 12:19:11 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/panels.h"



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
void 				create_figures(t_rt *s)
{
	int i = 0;

	s->scene.figures = (t_btn*)malloc(sizeof(t_btn) * s->scene.objnum + 1);
	while (i < (int)s->scene.objnum)
	{
		s->scene.figures[i].pressed = 0;
		s->scene.figures[i].name = i;
		s->scene.figures[i].rect = make_rect(230, i * 20 + 10, BUTTON_SIZE, BUTTON_SIZE);
		s->scene.figures[i].txt = load_texture(s->icon[s->scene.objs[i].type + 4], s);
		i++;
	}
//	s->scene.figures[i].pressed = 0;
//	s->scene.figures[i].name = i;
//	s->scene.figures[i].rect = make_rect(230, i * 20 + 10, BUTTON_SIZE, BUTTON_SIZE);
//	s->scene.figures[i].txt = load_texture(s->icon[13], s);

}
void 				put_figures(t_rt *s)
{
	int i = 0;
	while (i < (int)s->scene.objnum)
	{
		SDL_RenderCopy(s->sdl.renderer,
					   s->scene.figures[i].txt,
					   NULL, &s->scene.figures[i].rect);
		i++;
	}
}

void				show_settings(t_rt *s)
{
	SDL_Texture* bg;
	SDL_Rect backgroundPos;

	bg = s->textures[1];
	backgroundPos.y = 0;
	backgroundPos.w = 50;
	backgroundPos.h = s->sdl.win_w;
	backgroundPos.x = s->sdl.win_w - backgroundPos.w;
	SDL_RenderCopy(s->sdl.renderer, bg, NULL, &backgroundPos);

	put_figures(s);
}

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
				//start path tracing
			}
			else if (i == 1)
			{
				create_new_scene(s);
//				show_settings(s);
			}
//			else if (i > 3 && s->buttons[i].pressed)
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
	unsigned timeout;

	clSetKernelArg(s->kernel.kernel, 6, sizeof(cl_uint), &s->samples);
	fprintf(stderr, " samples per pixel -> %d\r", s->samples);
	s->samples++;
	timeout	= SDL_GetTicks() + 17;
	if (s->samples < 10)
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout))
		{
			rt_cl_push_task(&s->kernel, &s->job_size);
			rt_cl_join(&s->info);
		}
	else
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 150))
		{
			rt_cl_push_task(&s->kernel, &s->job_size);
			rt_cl_join(&s->info);
		}
	rt_cl_device_to_host(&s->info, s->pixels_mem,
			s->sdl.pixels, s->job_size * sizeof(int));
	SDL_UpdateTexture(s->sdl.canvas, NULL, s->sdl.pixels, s->sdl.win_w << 2);
	SDL_RenderClear(s->sdl.renderer);
	SDL_RenderCopy(s->sdl.renderer, s->sdl.canvas, NULL, NULL);
	set_panel(s);
	SDL_RenderPresent(s->sdl.renderer);
}
