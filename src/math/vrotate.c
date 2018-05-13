/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vrotate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 19:03:51 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/04/25 12:44:19 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float3	vrotate(cl_float3 v, cl_float3 *matrix)
{
	cl_float3 res;

	res = vadd(
			vmul(matrix[0], v.x),
			vadd(
				vmul(matrix[1], v.y),
				vmul(matrix[2], v.z)));
	return (res);
}
