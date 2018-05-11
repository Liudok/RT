/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 20:55:08 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/11 20:55:11 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void 	validation_mobius(t_mobius *o)
{
	if (o->origin.s0 > MAXF || o->origin.s0 < MINF ||
		o->origin.s1 > MAXF || o->origin.s1 < MINF ||
		o->origin.s2 > MAXF || o->origin.s2 < MINF)
	{
		ft_putendl_fd("ORIGIN of mobius is invalid", 2);
	}
	o->origin.s0 = (o->origin.s0 > MAXF) ? MAXF : o->origin.s0;
	o->origin.s1 = (o->origin.s1 > MAXF) ? MAXF : o->origin.s1;
	o->origin.s2 = (o->origin.s2 > MAXF) ? MAXF : o->origin.s2;
	o->origin.s0 = (o->origin.s0 < MINF) ? MINF : o->origin.s0;
	o->origin.s1 = (o->origin.s1 < MINF) ? MINF : o->origin.s1;
	o->origin.s2 = (o->origin.s2 < MINF) ? MINF : o->origin.s2;
	if (o->size > 0.4 || o->size < 0.1)
	{
		ft_putendl_fd("Invalid size of mobius", 2);
		o->size = 0.4;
	}
}

void 	validation_cube(t_cube *o)
{
	if (o->min.s0 > 500 || o->min.s0 < -500 ||
		o->min.s1 > 500 || o->min.s1 < -500 ||
		o->min.s2 > 500 || o->min.s2 < -500)
	{
		ft_putendl_fd("MIN of cube is invalid", 2);
	}
	o->min.s0 = (o->min.s0 > 500) ? 500 : o->min.s0;
	o->min.s1 = (o->min.s1 > 500) ? 500 : o->min.s1;
	o->min.s2 = (o->min.s2 > 500) ? 500 : o->min.s2;
	o->min.s0 = (o->min.s0 < -500) ? -500 : o->min.s0;
	o->min.s1 = (o->min.s1 < -500) ? -500 : o->min.s1;
	o->min.s2 = (o->min.s2 < -500) ? -500 : o->min.s2;
	if (o->max.s0 > 500 || o->max.s0 < -500 ||
		o->max.s1 > 500 || o->max.s1 < -500 ||
		o->max.s2 > 500 || o->max.s2 < -500)
	{
		ft_putendl_fd("MIN of cube is invalid", 2);
	}
	o->max.s0 = (o->max.s0 > 500) ? 500 : o->max.s0;
	o->max.s1 = (o->max.s1 > 500) ? 500 : o->max.s1;
	o->max.s2 = (o->max.s2 > 500) ? 500 : o->max.s2;
	o->max.s0 = (o->max.s0 < -500) ? -500 : o->max.s0;
	o->max.s1 = (o->max.s1 < -500) ? -500 : o->max.s1;
	o->max.s2 = (o->max.s2 < -500) ? -500 : o->max.s2;
	if (o->pipes_number > 14 || o->pipes_number < 0)
	{
		ft_putendl_fd("Invalid pipes_number of cube", 2);
		o->pipes_number = 0;
	}
}

void 	validation_parabaloid(t_parabaloid *o)
{
	if (o->origin.s0 > MAXF || o->origin.s0 < MINF ||
		o->origin.s1 > MAXF || o->origin.s1 < MINF ||
		o->origin.s2 > MAXF || o->origin.s2 < MINF)
	{
		ft_putendl_fd("ORIGIN of parabaloid is invalid", 2);
	}
	o->origin.s0 = (o->origin.s0 > MAXF) ? MAXF : o->origin.s0;
	o->origin.s1 = (o->origin.s1 > MAXF) ? MAXF : o->origin.s1;
	o->origin.s2 = (o->origin.s2 > MAXF) ? MAXF : o->origin.s2;
	o->origin.s0 = (o->origin.s0 < MINF) ? MINF : o->origin.s0;
	o->origin.s1 = (o->origin.s1 < MINF) ? MINF : o->origin.s1;
	o->origin.s2 = (o->origin.s2 < MINF) ? MINF : o->origin.s2;
	if (o->normal.s0 > 1 || o->normal.s0 < -1 ||
		o->normal.s1 > 1 || o->normal.s1 < -1 ||
		o->normal.s2 > 1 || o->normal.s2 < -1)
	{
		ft_putendl_fd("NORMAL of parabaloid is invalid", 2);
	}
	o->normal.s0 = (o->normal.s0 > 1) ? 1 : o->normal.s0;
	o->normal.s1 = (o->normal.s1 > 1) ? 1 : o->normal.s1;
	o->normal.s2 = (o->normal.s2 > 1) ? 1 : o->normal.s2;
	o->normal.s0 = (o->normal.s0 < -1) ? -1 : o->normal.s0;
	o->normal.s1 = (o->normal.s1 < -1) ? -1 : o->normal.s1;
	o->normal.s2 = (o->normal.s2 < -1) ? -1 : o->normal.s2;
	if (o->radius > MAXF || o->radius < MINF)
	{
		ft_putendl_fd("Invalid radius of parabaloid", 2);
		o->radius = 2;
	}
	if (o->max > MAXF || o->max < MINF)
	{
		ft_putendl_fd("Invalid max of parabaloid", 2);
		o->max = 2;
	}
}

void 	validation_julia(t_julia *o)
{
	if (o->c.s0 > 1 || o->c.s0 < -1 ||
			o->c.s1 > 1 || o->c.s1 < -1 ||
			o->c.s2 > 1 || o->c.s2 < -1 ||
			o->c.s3 > 1 || o->c.s3 < -1)
	{
		ft_putendl_fd("C of fractal julia is invalid", 2);
		o->c = (float4){{-0.450,-0.447,0.181,0.306}};
	}
}
