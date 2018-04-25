/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isCameraEvent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 18:21:36 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/04/25 12:44:19 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int isCameraEvent(t_rt *pt)
{
	if (pt->event.w || pt->event.s || pt->event.a || pt->event.d ||
		pt->event.q || pt->event.e || pt->event.up || pt->event.down ||
		pt->event.left || pt->event.right)
		return (TRUE);
	return (FALSE);
}
