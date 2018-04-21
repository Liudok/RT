/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   onEvent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 18:13:10 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/04/21 12:26:26 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	onEvent(t_rt *pt, SDL_Event *e)
{
	if (e->key.keysym.sym == SDLK_w)
		pt->event.w = 1;
	else if (e->key.keysym.sym == SDLK_s)
		pt->event.s = 1;
	else if (e->key.keysym.sym == SDLK_a)
		pt->event.a = 1;
	else if (e->key.keysym.sym == SDLK_d)
		pt->event.d = 1;
	else if (e->key.keysym.sym == SDLK_q)
		pt->event.q = 1;
	else if (e->key.keysym.sym == SDLK_e)
		pt->event.e = 1;
	else if (e->key.keysym.sym == SDLK_UP)
		pt->event.up = 1;
	else if (e->key.keysym.sym == SDLK_DOWN)
		pt->event.down = 1;
	else if (e->key.keysym.sym == SDLK_LEFT)
		pt->event.left = 1;
	else if (e->key.keysym.sym == SDLK_RIGHT)
		pt->event.right = 1;
}