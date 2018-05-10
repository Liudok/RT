/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 18:25:48 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/05/10 17:24:57 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	arrows(t_rt *rt, t_camera *c)
{
	if (rt->event.up)
		c->rotate.x += 1;
	if (rt->event.down)
		c->rotate.x -= 1;
	if (rt->event.left)
		c->rotate.y -= 1;
	if (rt->event.right)
		c->rotate.y += 1;
	if (rt->event.up || rt->event.down || rt->event.left || rt->event.right)
		rotate_camera(rt);
}

void		update_camera(t_rt *rt)
{
	t_camera	*c;

	rt->samples = rt->effect_type == 1 ? 1 : 0;
	c = &rt->scene.camera;
	if (rt->event.w)
		c->origin = vadd(c->origin, vmul(normalize(c->dir), 0.2));
	if (rt->event.s)
		c->origin = vsub(c->origin, vmul(normalize(c->dir), 0.2));
	if (rt->event.d)
		c->origin = vadd(c->origin, vmul(normalize(c->cx), 0.2));
	if (rt->event.a)
		c->origin = vsub(c->origin, vmul(normalize(c->cx), 0.2));
	if (rt->event.q)
		c->origin = vadd(c->origin, vmul(normalize(c->cy), 0.2));
	if (rt->event.e)
		c->origin = vsub(c->origin, vmul(normalize(c->cy), 0.2));
	arrows(rt, c);
	clSetKernelArg(rt->kernel.kernel, 2, sizeof(t_camera), &rt->scene.camera);
}
