/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 12:57:30 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/12 12:57:33 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libJSON/include/json.h"
#include "../../include/rt.h"

float				get_number(json_value *value)
{
	float		ret;

	ret = 0;
	if (value->type == json_integer)
		ret = (float)value->u.integer;
	else if (value->type == json_double)
		ret = (float)value->u.dbl;
	else
	{
		ft_putendl_fd("Not a number format where expected", 2);
		g_error_flag = 1;
	}
	return (ret);
}

cl_float4			get_float4(json_value *value)
{
	cl_float4		ret;

	ret = (cl_float4){{0, 0, 0, 0}};
	if (value == NULL || value->type != json_array ||
		value->u.array.length != 4)
		ft_error("No value for float4.");
	ret.s0 = get_number(value->u.array.values[0]);
	ret.s1 = get_number(value->u.array.values[1]);
	ret.s2 = get_number(value->u.array.values[2]);
	ret.s3 = get_number(value->u.array.values[3]);
	if (ret.s0 > 1 || ret.s0 < 0 || ret.s1 > 1 || ret.s1 < 0 ||
		ret.s2 > 1 || ret.s2 < 0 || ret.s3 > 1 || ret.s3 < 0)
	{
		ft_putendl_fd("The value in material can't be > 1 or < 0", 2);
		return (ret);
	}
	return (ret);
}

cl_float3			get_float3(json_value *value)
{
	cl_float3		ret;

	ret = (cl_float3){{0, 0, 0}};
	if (value == NULL || value->type != json_array ||
		value->u.array.length != 3)
	{
		ft_putendl_fd("No value for float3.", 2);
		g_error_flag = 1;
		return (ret);
	}
	ret.s0 = get_number(value->u.array.values[0]);
	ret.s1 = get_number(value->u.array.values[1]);
	ret.s2 = get_number(value->u.array.values[2]);
	return (ret);
}

cl_uchar4			get_uchar4(json_value *value)
{
	cl_uchar4		ret;

	ret = (cl_uchar4){{0, 0, 0, 0}};
	if (value == NULL || value->type != json_array ||
		value->u.array.length != 4)
	{
		ft_putendl_fd("No value for uchar4.", 2);
		return (ret);
	}
	ret.s0 = get_number(value->u.array.values[0]);
	ret.s1 = get_number(value->u.array.values[1]);
	ret.s2 = get_number(value->u.array.values[2]);
	ret.s3 = get_number(value->u.array.values[3]);
	return (ret);
}
