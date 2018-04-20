/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vrotate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 19:03:51 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/04/19 19:03:52 by ftymchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pt.h"

float3	vrotate(float3 v, float3 *matrix)
{
	float3 res;

	res = vadd(
			vmul(matrix[0], v.x),
			vadd(
				vmul(matrix[1], v.y),
				vmul(matrix[2], v.z)));
	return (res);
}
