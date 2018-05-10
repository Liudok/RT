/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rotation_matrix.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 19:03:35 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/05/10 17:41:53 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	create_rotation_matrix(t_rt *rt, float3 *m)
{
	float3		tmp[3];
	int			i;
	double		x;
	double		y;

	tmp[0] = (float3){{1, 0, 0}};
	tmp[1] = (float3){{0, 1, 0}};
	tmp[2] = (float3){{0, 0, 1}};
	i = 0;
	x = rt->scene.camera.rotate.x * M_PI / 180.0;
	y = rt->scene.camera.rotate.y * M_PI / 180.0;
	while (i < 3)
	{
		m[i].x =
			dot((float3){{cos(y), sin(y) * -sin(x), sin(y) * cos(x)}}, tmp[i]);
		m[i].y =
			dot((float3){{0, cos(x), sin(x)}}, tmp[i]);
		m[i].z =
			dot((float3){{-sin(y), cos(y) * -sin(x), cos(y) * cos(x)}}, tmp[i]);
		i++;
	}
}
