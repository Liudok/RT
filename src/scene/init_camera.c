/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 16:11:43 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/04/18 16:11:44 by ftymchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pt.h"

//void	init_camera(float3 pos, t_pt *pt)
//{
//	t_camera	*cam;
//
//	cam = &pt->scene.camera;
//	cam->canvas = (int2){{pt->sdl.width, pt->sdl.height}};
//	cam->origin = pos;
//	cam->dir = (float3){{0, 0, 1}};
//	cam->cx = (float3){{cam->canvas.x * .5135 / (float)cam->canvas.y, 0, 0}};
//	cam->cy = vmul(normalize(cross(cam->cx, cam->dir)), .5135);
//}
