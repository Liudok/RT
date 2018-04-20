/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 18:06:51 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/03/19 18:06:53 by ftymchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pt.h"

float3	normalize(float3 v)
{
	double len;
	double inv_len;

	len = vlen(v);
	if (len > 0)
	{
		inv_len = 1.0 / len;
		return (vmul(v, inv_len));
	}
	return (v);
}
