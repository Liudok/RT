/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_gui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 12:01:03 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/12 12:01:07 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/panels.h"

cl_float		my_atof(const char *val, float min, float max)
{
	cl_float	ret;

	ret = (cl_float)atof(val);
	if (ret < min)
		ret = min;
	else if (ret > max)
		ret = max;
	return (ret);
}

cl_uchar		my_uchar(const char *val, float min, float max)
{
	cl_uchar	ret;
	int			int_ret;

	int_ret = ft_atoi(val);
	if (int_ret < min)
		int_ret = min;
	else if (int_ret > max)
		int_ret = max;
	ret = (cl_uchar)int_ret;
	return (ret);
}

void			fill_texture(const float **ptr, t_sdl *s,
							t_rec *recs, cl_uint2 n)
{
	uint		i;
	char		text[20];

	i = (uint)-1;
	while (++i < n.x)
	{
		sprintf(text, "%.2f       ", *(ptr[i]));
		texture_from_text(text, s, &recs[i + n.y]);
	}
}
