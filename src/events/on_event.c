/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 18:13:10 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/05/10 15:52:17 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	on_event(t_rt *rt, SDL_Event *e)
{
	if (e->key.keysym.sym == SDLK_w)
		rt->event.w = 1;
	else if (e->key.keysym.sym == SDLK_s)
		rt->event.s = 1;
	else if (e->key.keysym.sym == SDLK_a)
		rt->event.a = 1;
	else if (e->key.keysym.sym == SDLK_d)
		rt->event.d = 1;
	else if (e->key.keysym.sym == SDLK_q)
		rt->event.q = 1;
	else if (e->key.keysym.sym == SDLK_e)
		rt->event.e = 1;
	else if (e->key.keysym.sym == SDLK_UP)
		rt->event.up = 1;
	else if (e->key.keysym.sym == SDLK_DOWN)
		rt->event.down = 1;
	else if (e->key.keysym.sym == SDLK_LEFT)
		rt->event.left = 1;
	else if (e->key.keysym.sym == SDLK_RIGHT)
		rt->event.right = 1;
}
