/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_setting_win_textures.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 15:43:38 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/11 23:37:45 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/panels.h"

void		fill_texture(const float **ptr, t_sdl *s, t_rec *recs, cl_uint2 n)
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

void		real_tria_mobius_texture(t_object *o, t_sdl *sdl, t_rec *recs)
{
	const float *triangle_ptr[] = {&o->prim.triangle.vertex0.s0,
		&o->prim.triangle.vertex0.s1, &o->prim.triangle.vertex0.s2,
		&o->prim.triangle.vertex1.s0, &o->prim.triangle.vertex1.s1,
		&o->prim.triangle.vertex1.s2, &o->prim.triangle.vertex2.s0,
		&o->prim.triangle.vertex2.s1, &o->prim.triangle.vertex2.s2};
	const float *cube_ptr[] = {&o->prim.cube.min.s0, &o->prim.cube.min.s1,
		&o->prim.cube.min.s2, &o->prim.cube.max.s0, &o->prim.cube.max.s1,
		&o->prim.cube.max.s2};
	const float *mobius_ptr[] = {&o->prim.mobius.origin.s0,
		&o->prim.mobius.origin.s1};

	if (o->type == triangle)
		fill_texture(triangle_ptr, sdl, recs,
				(cl_uint2){{ sizeof(triangle_ptr) / sizeof(void *), 20}});
	else if (o->type == mobius)
		fill_texture(triangle_ptr, sdl, recs,
				(cl_uint2){{ sizeof(mobius_ptr) / sizeof(void *), 18}});
	else if (o->type == cube)
		fill_texture(triangle_ptr, sdl, recs,
				(cl_uint2){{ sizeof(cube_ptr) / sizeof(void *), 20}});
}

void		real_set_other_prims_fields(t_object *o, t_sdl *sdl, t_rec *recs)
{
	const float *ptrs[] = {&o->prim.plane.normal.x, &o->prim.plane.normal.y,
		&o->prim.plane.normal.z};
	char text[20];

	if (o[0].type == plane || o[0].type == cylinder ||
		o[0].type == cone || o[0].type == disk || o[0].type == torus)
		fill_texture(ptrs, sdl, recs,
				(cl_uint2){{ sizeof(ptrs) / sizeof(void *), 23}});
	else if (o[0].type == sphere)
	{
		sprintf(text, "%.2f       ", o[0].prim.sphere.radius);
		texture_from_text(text, sdl, &recs[23]);
	}
	if (o[0].type == cylinder || o[0].type == disk || o[0].type == cone)
	{
		sprintf(text, "%.2f       ", o[0].prim.disk.radius2);
		texture_from_text(text, sdl, &recs[26]);
	}
	if (o[0].type == cylinder)
	{
		sprintf(text, "%.2f       ", o[0].prim.cylinder.height);
		texture_from_text(text, sdl, &recs[27]);
	}
	else if (o[0].type == cone)
	{
		sprintf(text, "%.2f       ", o[0].prim.cone.m1);
		texture_from_text(text, sdl, &recs[27]);
		sprintf(text, "%.2f       ", o[0].prim.cone.m2);
		texture_from_text(text, sdl, &recs[28]);
	}
	else if (o[0].type == torus)
	{
		sprintf(text, "%.2f       ", o[0].prim.torus.big_radius2);
		texture_from_text(text, sdl, &recs[26]);
		sprintf(text, "%.2f       ", o[0].prim.torus.small_radius2);
		texture_from_text(text, sdl, &recs[27]);
	}
}

void		real_settings_rect_params(t_rec *recs, int prop)
{
	int		i;

	i = 10;
	while (i < prop)
	{
		if (i < 13) //color
		{
			recs[i].rect.x = 200 + (i % 10) * 100;
			recs[i].rect.y = 40;
		}
		else if (i < 14)//material
		{
			recs[i].rect.x = 200;
			recs[i].rect.y = 80;
		}
		else if (i < 15)//roug
		{
			recs[i].rect.x = 200;
			recs[i].rect.y = 120;
		}
		else if (i < 16)//ior
		{
			recs[i].rect.x = 200;
			recs[i].rect.y = 160;
		}
		else if (i < 20)//texture
		{
			recs[i].rect.x = 200 + (i % 16) * 80;
			recs[i].rect.y = 200;
		}
		else if (i < 23)//origin for all but triangle and mobius
		{
			recs[i].rect.x = 200 + (i % 20) * 100;
			recs[i].rect.y = 240;
		}
		else if (i < 26) //normal
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
		i++;
	}
}

void		real_create_color_texture(t_object *o, t_sdl *sdl, t_rec *recs)
{
	char text[20];

	sprintf(text, "%.2f       ", o->color.x);
	texture_from_text(text, sdl, &recs[10]);
	sprintf(text, "%.2f       ", o->color.y);
	texture_from_text(text, sdl, &recs[11]);
	sprintf(text, "%.2f       ", o->color.z);
	texture_from_text(text, sdl, &recs[12]);

	sprintf(text, "%i       ", o->material);
	texture_from_text(text, sdl, &recs[13]);
	sprintf(text, "%.2f       ", o->roughness);
	texture_from_text(text, sdl, &recs[14]);
	sprintf(text, "%.1f       ", o->ior);
	texture_from_text(text, sdl, &recs[15]);

	sprintf(text, "%.0f       ", (double)o->texture.s0);
	texture_from_text(text, sdl, &recs[16]);
	sprintf(text, "%.0f       ", (double)o->texture.s1);
	texture_from_text(text, sdl, &recs[17]);
	sprintf(text, "%.0f       ", (double)o->texture.s2);
	texture_from_text(text, sdl, &recs[18]);
	sprintf(text, "%.0f       ", (double)o->texture.s3);
	texture_from_text(text, sdl, &recs[19]);
}

void		real_values(t_object *o, t_sdl *sdl, t_rec *recs)
{
	int		prop;
	char text[20];

	prop = this_figure_props(o->type);
	real_create_color_texture(o, sdl, recs);
	if (o->type != triangle && o->type != mobius && o->type != cube)
	{
		sprintf(text, "%.2f       ", o->prim.plane.origin.x);
		texture_from_text(text, sdl, &recs[20]);
		sprintf(text, "%.2f       ", o->prim.plane.origin.y);
		texture_from_text(text, sdl, &recs[21]);
		sprintf(text, "%.2f       ", o->prim.plane.origin.z);
		texture_from_text(text, sdl, &recs[22]);
		real_set_other_prims_fields(o, sdl, recs);
	}
	else
		real_tria_mobius_texture(o, sdl, recs);
	real_settings_rect_params(recs, prop);
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
