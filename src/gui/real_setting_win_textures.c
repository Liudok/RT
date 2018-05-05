/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_setting_win_textures.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 15:43:38 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/02 15:43:41 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/panels.h"

void		real_other_prim_3_texture(t_object *o, t_sdl *sdl, t_rec *recs)
{
	if (o[0].type == triangle)
	{
		texture_from_text("Vertex 0:", sdl, &recs[3]);
		texture_from_text("Vertex 1:", sdl, &recs[4]);
		texture_from_text("Vertex 2:", sdl, &recs[5]);
	}
	else if (o[0].type == mobius)
	{
		texture_from_text("Radius:", sdl, &recs[3]);
		texture_from_text("Half_width:", sdl, &recs[4]);
	}
}

void		real_set_other_prims_fields(t_object *o, t_sdl *sdl, t_rec *recs)
{
	char text[20];

	if (o[0].type == plane || o[0].type == cylinder ||
		o[0].type == cone || o[0].type == disk || o[0].type == torus)
	{
		sprintf(text, "%.2f       ", o[0].prim.plane.normal.s0);
		texture_from_text(text, sdl, &recs[21]);
		sprintf(text, "%.2f       ", o[0].prim.plane.normal.s1);
		texture_from_text(text, sdl, &recs[22]);
		sprintf(text, "%.2f       ", o[0].prim.plane.normal.s2);
		texture_from_text(text, sdl, &recs[23]);
	}
	else if (o[0].type == sphere)
	{
		sprintf(text, "%.2f       ", o[0].prim.sphere.radius);
		texture_from_text(text, sdl, &recs[21]);
	}
	if (o[0].type == cylinder || o[0].type == disk || o[0].type == torus)
	{
		sprintf(text, "%.2f       ", o[0].prim.disk.radius2);
		texture_from_text(text, sdl, &recs[24]);
	}
	if (o[0].type == cylinder)
		texture_from_text("Height:", sdl, &recs[6]);
	else if (o[0].type == cone)
	{
		texture_from_text("Half_tangent:", sdl, &recs[5]);
		texture_from_text("M1:", sdl, &recs[6]);
		texture_from_text("M2:", sdl, &recs[7]);
	}
	else if (o[0].type == torus)
		texture_from_text("Big radius:", sdl, &recs[6]);
}


void		real_settings_rect_params(t_rec *recs)
{
	int		i;

	i = 8;
	while (i < PROPERTIES)
	{
		if (i < 11)
		{
			printf("PROP i = %i", i);
			recs[i].rect.x = 200 + (i % 8) * 60;
			recs[i].rect.y = 40;
		}
		else if (i < 15)
		{
			recs[i].rect.x = 200 + (i % 11) * 50;
			recs[i].rect.y = 80;
		}
		else if (i < 18)
		{
			recs[i].rect.x = 200 + (i % 15) * 50;
			recs[i].rect.y = 120;
		}
		else if (i < 21)
		{
			recs[i].rect.x = 200 + (i % 18) * 60;
			recs[i].rect.y = 160;
		}
		else if (i < 24)
		{
			recs[i].rect.x = 200 + (i % 21) * 60;
			recs[i].rect.y = 200;
		}
		else if (i < 25)
		{
			recs[i].rect.x = 200 + (i % 24) * 60;
			recs[i].rect.y = 240;
		}
		i++;
	}
}

void		real_create_settings_textures(t_rt *rt, t_sdl *sdl, t_rec *recs, int i)
{
	char text[20];

	sprintf(text, "%.2f       ", rt->scene.objs[i].color.x);
	texture_from_text(text, sdl, &recs[8]);
	sprintf(text, "%.2f       ", rt->scene.objs[i].color.y);
	texture_from_text(text, sdl, &recs[9]);
	sprintf(text, "%.2f       ", rt->scene.objs[i].color.z);
	texture_from_text(text, sdl, &recs[10]);

	sprintf(text, "%.0f       ", rt->scene.objs[i].material.s0);
	texture_from_text(text, sdl, &recs[11]);
	sprintf(text, "%.0f       ", rt->scene.objs[i].material.s1);
	texture_from_text(text, sdl, &recs[12]);
	sprintf(text, "%.0f       ", rt->scene.objs[i].material.s2);
	texture_from_text(text, sdl, &recs[13]);
	sprintf(text, "%.0f       ", rt->scene.objs[i].material.s3);
	texture_from_text(text, sdl, &recs[14]);

	sprintf(text, "%.0f       ", (double)rt->scene.objs[i].texture.s0);
	texture_from_text(text, sdl, &recs[15]);
	sprintf(text, "%.0f       ", (double)rt->scene.objs[i].texture.s1);
	texture_from_text(text, sdl, &recs[16]);
	sprintf(text, "%.0f       ", (double)rt->scene.objs[i].texture.s2);
	texture_from_text(text, sdl, &recs[17]);
	if (rt->scene.objs[i].type == sphere ||
			rt->scene.objs[i].type == plane ||
			rt->scene.objs[i].type == cylinder ||
			rt->scene.objs[i].type == cone ||
			rt->scene.objs[i].type == disk ||
			rt->scene.objs[i].type == torus)
	{
		sprintf(text, "%.2f       ", rt->scene.objs[i].prim.plane.origin.x);
		texture_from_text(text, sdl, &recs[18]);
		sprintf(text, "%.2f       ", rt->scene.objs[i].prim.plane.origin.y);
		texture_from_text(text, sdl, &recs[19]);
		sprintf(text, "%.2f       ", rt->scene.objs[i].prim.plane.origin.z);
		texture_from_text(text, sdl, &recs[20]);
		real_set_other_prims_fields(&rt->scene.objs[i], sdl, recs);
	}
//	else
//		real_other_prim_3_texture(&rt->scene.objs[i], sdl, recs);
	real_settings_rect_params(recs);
}
