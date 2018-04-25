/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_window_resizable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:38:27 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/04/19 15:38:28 by ftymchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	is_window_resizable(SDL_Event e)
{
	return (e.type == SDL_WINDOWEVENT &&
			e.window.event == SDL_WINDOWEVENT_RESIZED);
}
