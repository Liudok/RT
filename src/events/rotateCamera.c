/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotateCamera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 19:16:09 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/04/25 12:44:19 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rotateCamera(t_rt *pt)
{
	t_camera	*c;
	float3 		matrix[3];

	c = &pt->scene.camera;
	init_camera(pt);
	createRotationMatrix(pt, matrix);
	c->dir = vrotate(c->dir, matrix);
	c->cx = vrotate(c->cx, matrix);
	c->cy = vrotate(c->cy, matrix);
}
