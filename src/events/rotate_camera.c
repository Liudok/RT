/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 19:16:09 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/04/19 19:16:11 by ftymchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rotate_camera(t_rt *rt)
{
	t_camera	*c;
	float3 		matrix[3];

	c = &rt->scene.camera;
	init_camera(rt, c->origin);
	create_rotation_matrix(rt, matrix);
	c->dir = vrotate(c->dir, matrix);
	c->cx = vrotate(c->cx, matrix);
	c->cy = vrotate(c->cy, matrix);
}
