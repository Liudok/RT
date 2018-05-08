/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_win_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 15:43:38 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/02 15:43:41 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/panels.h"

void		other_prim_3_texture(t_object *o, t_sdl *sdl, t_rec *recs)
{
	if (o[0].type == triangle)
	{
		texture_from_text("Vertex 0:", sdl, &recs[5]);
		texture_from_text("Vertex 1:", sdl, &recs[6]);
		texture_from_text("Vertex 2:", sdl, &recs[7]);
	}
	else if (o[0].type == mobius)
	{
		texture_from_text("Radius:", sdl, &recs[5]);
		texture_from_text("Half_width:", sdl, &recs[6]);
	}
	else if (o[0].type == cube)
	{
		texture_from_text("Min:", sdl, &recs[5]);
		texture_from_text("Max:", sdl, &recs[6]);
	}
}

void		set_other_prims_fields(t_object *o, t_sdl *sdl, t_rec *recs)
{
	if (o[0].type == plane || o[0].type == cylinder ||
		o[0].type == cone || o[0].type == disk || o[0].type == torus)
	{
		texture_from_text("Normal:", sdl, &recs[6]);
	}
	else if (o[0].type == sphere)
		texture_from_text("Radius:", sdl, &recs[6]);
	if (o[0].type == cylinder || o[0].type == disk || o[0].type == torus)
		texture_from_text("Radius:", sdl, &recs[7]);
	if (o[0].type == cylinder)
		texture_from_text("Height:", sdl, &recs[8]);
	else if (o[0].type == cone)
	{
		texture_from_text("Half_tangent:", sdl, &recs[7]);
		texture_from_text("M1:", sdl, &recs[8]);
		texture_from_text("M2:", sdl, &recs[9]);
	}
	else if (o[0].type == torus)
		texture_from_text("Big radius:", sdl, &recs[8]);
}

void		settings_rect_params(t_rec *recs)
{
	int		i;
	int		y;

	i = 0;
	y = 20;
	while (i < 10)
	{
		recs[i].rect.x = 40;
		recs[i].rect.y = y * 2;
		y += 20;
		i++;
	}
}

void		create_settings_textures(t_rt *rt, t_sdl *sdl, t_rec *recs, int i)
{
	texture_from_text("Color:", sdl, &recs[0]);
	texture_from_text("Material:", sdl, &recs[1]);
	texture_from_text("Roughness:", sdl, &recs[2]);
	texture_from_text("Ior:", sdl, &recs[3]);
	texture_from_text("Texture:", sdl, &recs[4]);
	if (rt->scene.objs[i].type == sphere ||
			rt->scene.objs[i].type == plane ||
			rt->scene.objs[i].type == cylinder ||
			rt->scene.objs[i].type == cone ||
			rt->scene.objs[i].type == disk ||
			rt->scene.objs[i].type == torus)
	{
		texture_from_text("Origin:", sdl, &recs[5]);
		set_other_prims_fields(&rt->scene.objs[i], sdl, recs);
	}
	else
		other_prim_3_texture(&rt->scene.objs[i], sdl, recs);
	settings_rect_params(recs);
}
