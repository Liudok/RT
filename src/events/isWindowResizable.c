/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isWindowResizable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:38:27 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/04/21 12:26:26 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	isWindowResizable(SDL_Event e)
{
	return (e.type == SDL_WINDOWEVENT &&
			e.window.event == SDL_WINDOWEVENT_RESIZED);
}
