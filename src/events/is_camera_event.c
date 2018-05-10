/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_camera_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 18:21:36 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/05/10 15:50:45 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	is_camera_event(t_rt *rt)
{
	if (rt->event.w || rt->event.s || rt->event.a || rt->event.d ||
		rt->event.q || rt->event.e || rt->event.up || rt->event.down ||
		rt->event.left || rt->event.right)
		return (TRUE);
	return (FALSE);
}
