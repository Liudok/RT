/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   off_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 18:13:23 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/04/19 18:13:24 by ftymchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	off_event(t_rt *rt, SDL_Event *e)
{
	if (e->key.keysym.sym == SDLK_w)
		rt->event.w = 0;
	else if (e->key.keysym.sym == SDLK_s)
		rt->event.s = 0;
	else if (e->key.keysym.sym == SDLK_a)
		rt->event.a = 0;
	else if (e->key.keysym.sym == SDLK_d)
		rt->event.d = 0;
	else if (e->key.keysym.sym == SDLK_q)
		rt->event.q = 0;
	else if (e->key.keysym.sym == SDLK_e)
		rt->event.e = 0;
	else if (e->key.keysym.sym == SDLK_UP)
		rt->event.up = 0;
	else if (e->key.keysym.sym == SDLK_DOWN)
		rt->event.down = 0;
	else if (e->key.keysym.sym == SDLK_LEFT)
		rt->event.left = 0;
	else if (e->key.keysym.sym == SDLK_RIGHT)
		rt->event.right = 0;
}
