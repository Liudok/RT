/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offEvent.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 18:13:23 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/04/19 18:13:24 by ftymchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pt.h"

void	offEvent(t_pt *pt, SDL_Event *e)
{
	if (e->key.keysym.sym == SDLK_w)
		pt->event.w = 0;
	else if (e->key.keysym.sym == SDLK_s)
		pt->event.s = 0;
	else if (e->key.keysym.sym == SDLK_a)
		pt->event.a = 0;
	else if (e->key.keysym.sym == SDLK_d)
		pt->event.d = 0;
	else if (e->key.keysym.sym == SDLK_q)
		pt->event.q = 0;
	else if (e->key.keysym.sym == SDLK_e)
		pt->event.e = 0;
	else if (e->key.keysym.sym == SDLK_UP)
		pt->event.up = 0;
	else if (e->key.keysym.sym == SDLK_DOWN)
		pt->event.down = 0;
	else if (e->key.keysym.sym == SDLK_LEFT)
		pt->event.left = 0;
	else if (e->key.keysym.sym == SDLK_RIGHT)
		pt->event.right = 0;
}
