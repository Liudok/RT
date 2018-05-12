/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:30:25 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/09 14:30:28 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int		validation(t_object *o)
{
	if (o->material > 5)
	{
		ft_putendl_fd("Material can not be more than 4 or less than 0", 2);
		return (0);
	}
	if (o->roughness > 1 || o->roughness < 0)
	{
		ft_putendl_fd("Roughness can not be more than 1 or less than 0", 2);
		return (0);
	}
	if (o->ior > 2.6 || o->ior < 1)
	{
		ft_putendl_fd("Ior can not be more than 2.6 or less than 1", 2);
		return (0);
	}
	if (o->texture.s0 > 255 || o->texture.s0 < 0 ||
			o->texture.s1 > 255 || o->texture.s1 < 0 ||
			o->texture.s2 > 255 || o->texture.s2 < 0 ||
			o->texture.s3 > 255 || o->texture.s3 < 0)
	{
		ft_putendl_fd("Texture can't be more than 255 or less than 1", 2);
		return (0);
	}
	return (1);
}

void	validation_fix(t_object *o)
{
	if (o->material > 5)
		o->material = 0;
	if (o->roughness > 1 || o->roughness < 0)
		o->roughness = 0;
	if (o->ior > 2.6 || o->ior < 1)
		o->ior = 1.5;
	if (o->texture.s0 > 255 || o->texture.s0 < 0 ||
		o->texture.s1 > 255 || o->texture.s1 < 0 ||
		o->texture.s2 > 255 || o->texture.s2 < 0 ||
		o->texture.s3 > 255 || o->texture.s3 < 0)
	{
		o->texture = (uchar4){{0, 0, 0, 0}};
	}
}
