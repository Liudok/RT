/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 14:56:22 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/04/18 14:56:23 by ftymchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pt.h"

t_object	new_object
	(t_obj_type type, t_primitive prim, float4 material, float3 color)
{
	t_object obj;

	obj.type = type;
	obj.prim = prim;
	obj.material = material;
	obj.color = color;
	return (obj);
}
