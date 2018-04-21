/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updateCamera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 18:25:48 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/04/21 12:26:26 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	updateCamera(t_rt *pt)
{
	t_camera	*c;

	pt->samples = 0;
	c = &pt->scene.camera;
	if (pt->event.w)
		c->origin = vadd(c->origin, vmul(normalize(c->dir), 0.2));
	if (pt->event.s)
		c->origin = vsub(c->origin, vmul(normalize(c->dir), 0.2));
	if (pt->event.d)
		c->origin = vadd(c->origin, vmul(normalize(c->cx), 0.2));
	if (pt->event.a)
		c->origin = vsub(c->origin, vmul(normalize(c->cx), 0.2));
	if (pt->event.q)
		c->origin = vadd(c->origin, vmul(normalize(c->cy), 0.2));
	if (pt->event.e)
		c->origin = vsub(c->origin, vmul(normalize(c->cy), 0.2));
	if (pt->event.up)
		c->rotate.x += 0.5;
	if (pt->event.down)
		c->rotate.x -= 0.5;
	if (pt->event.left)
		c->rotate.y -= 0.5;
	if (pt->event.right)
		c->rotate.y += 0.5;
	if (pt->event.up || pt->event.down || pt->event.left || pt->event.right)
		rotateCamera(pt);
	clSetKernelArg(pt->kernel.kernel, 2, sizeof(t_camera), &pt->scene.camera);
}
