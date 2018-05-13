/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rects_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 12:19:38 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/12 12:19:41 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/panels.h"

void		real_settings_rect_params2(t_rec *recs, int i)
{
	if (i < 23)
	{
		recs[i].rect.x = 200 + (i % 20) * 100;
		recs[i].rect.y = 240;
	}
	else if (i < 26)
	{
		recs[i].rect.x = 200 + (i % 23) * 100;
		recs[i].rect.y = 280;
	}
	else if (i < 27)
	{
		recs[i].rect.x = 200;
		recs[i].rect.y = 320;
	}
	else if (i < 29)
	{
		recs[i].rect.x = 200 + (i % 27) * 100;
		recs[i].rect.y = 360;
	}
}

void		real_settings_rect_params(t_rec *recs, int prop)
{
	int		i;

	i = 9;
	while (++i < prop)
	{
		if (i < 13)
		{
			recs[i].rect.x = 200 + (i % 10) * 100;
			recs[i].rect.y = 40;
		}
		else if (i < 16)
		{
			recs[i].rect.x = 200;
			i == 13 ? recs[i].rect.y = 80 : (0);
			i == 14 ? recs[i].rect.y = 120 : (0);
			i == 15 ? recs[i].rect.y = 160 : (0);
		}
		else if (i < 20)
		{
			recs[i].rect.x = 200 + (i % 16) * 80;
			recs[i].rect.y = 200;
		}
		else if (i < 29)
			real_settings_rect_params2(recs, i);
	}
}

void		recs_correction(t_rec *recs, t_object *o)
{
	if (o->type == cone)
	{
		recs[28].rect.x = 200;
		recs[28].rect.y = 400;
	}
	else if (o->type == triangle)
	{
		recs[27].rect.x = 300;
		recs[27].rect.y = 320;
		recs[28].rect.x = 400;
		recs[28].rect.y = 320;
	}
}
