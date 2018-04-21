/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 14:56:12 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/04/18 14:56:13 by ftymchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pt.h"

t_primitive	new_sphere(float3 origin, float radius)
{
	t_primitive prim;

	prim.sphere.origin = origin;
	prim.sphere.radius = radius;
	prim.sphere.r2 = radius * radius;
	return (prim);
}
