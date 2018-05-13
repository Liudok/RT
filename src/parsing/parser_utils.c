/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 12:50:27 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/12 12:50:29 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libJSON/include/json.h"
#include "../../include/rt.h"

t_material		get_material(json_value *value)
{
	if (value->type != json_string)
	{
		ft_putendl_fd("Not valid json type..", 2);
		return (diffuse);
	}
	if (!ft_strcmp(value->u.string.ptr, "diffuse"))
		return (diffuse);
	else if (!ft_strcmp(value->u.string.ptr, "specular"))
		return (specular);
	else if (!ft_strcmp(value->u.string.ptr, "glass"))
		return (glass);
	else if (!ft_strcmp(value->u.string.ptr, "emission"))
		return (emission);
	else if (!ft_strcmp(value->u.string.ptr, "transparent"))
		return (transparent);
	else
		return (diffuse);
}

t_obj_type		get_type2(json_value *value)
{
	if (!ft_strncmp(value->u.string.ptr, "triangle", 8))
		return (triangle);
	else if (!ft_strncmp(value->u.string.ptr, "cube", 4))
		return (cube);
	else if (!ft_strncmp(value->u.string.ptr, "parabaloid", 10))
		return (parabaloid);
	else if (!ft_strncmp(value->u.string.ptr, "bool_substraction", 17))
		return (bool_substraction);
	else if (!ft_strncmp(value->u.string.ptr, "bool_intersection", 17))
		return (bool_intersection);
	else if (!ft_strncmp(value->u.string.ptr, "julia", 5))
		return (julia);
	ft_putendl_fd("Not valid object type", 2);
	g_error_flag = 1;
	return (not_valid);
}

t_obj_type		get_type(json_value *value)
{
	if (value->type != json_string)
	{
		ft_putendl_fd("Not valid json type", 2);
		g_error_flag = 1;
		return (not_valid);
	}
	if (!ft_strncmp(value->u.string.ptr, "plane", 5))
		return (plane);
	else if (!ft_strncmp(value->u.string.ptr, "sphere", 6))
		return (sphere);
	else if (!ft_strncmp(value->u.string.ptr, "cylinder", 8))
		return (cylinder);
	else if (!ft_strncmp(value->u.string.ptr, "cone", 4))
		return (cone);
	else if (!ft_strncmp(value->u.string.ptr, "disk", 4))
		return (disk);
	else if (!ft_strncmp(value->u.string.ptr, "torus", 5))
		return (torus);
	else if (!ft_strncmp(value->u.string.ptr, "mobius", 6))
		return (mobius);
	else
		return (get_type2(value));
}
