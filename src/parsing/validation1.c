/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 20:55:08 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/11 20:55:11 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	validation_sphere(t_sphere *o)
{
	if (o->origin.s0 > MAXF || o->origin.s0 < MINF ||
		o->origin.s1 > MAXF || o->origin.s1 < MINF ||
		o->origin.s2 > MAXF || o->origin.s2 < MINF)
	{
		ft_putendl_fd("ORIGIN of sphere is invalid", 2);
	}
	o->origin.s0 = (o->origin.s0 > MAXF) ? MAXF : o->origin.s0;
	o->origin.s1 = (o->origin.s1 > MAXF) ? MAXF : o->origin.s1;
	o->origin.s2 = (o->origin.s2 > MAXF) ? MAXF : o->origin.s2;
	o->origin.s0 = (o->origin.s0 < MINF) ? MINF : o->origin.s0;
	o->origin.s1 = (o->origin.s1 < MINF) ? MINF : o->origin.s1;
	o->origin.s2 = (o->origin.s2 < MINF) ? MINF : o->origin.s2;
	if (o->radius > MAXF || o->radius < MINF)
	{
		ft_putendl_fd("Invalid radius of sphere", 2);
		o->radius = 5;
		o->r2 = o->radius * o->radius;
	}
}

void	validation_plane(t_plane *o)
{
	if (o->origin.s0 > MAXF || o->origin.s0 < MINF ||
		o->origin.s1 > MAXF || o->origin.s1 < MINF ||
		o->origin.s2 > MAXF || o->origin.s2 < MINF)
	{
		ft_putendl_fd("ORIGIN of plane is invalid", 2);
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
		ft_putendl_fd("NORMAL of plane is invalid", 2);
	}
	o->normal.s0 = (o->normal.s0 > 1) ? 1 : o->normal.s0;
	o->normal.s1 = (o->normal.s1 > 1) ? 1 : o->normal.s1;
	o->normal.s2 = (o->normal.s2 > 1) ? 1 : o->normal.s2;
	o->normal.s0 = (o->normal.s0 < -1) ? -1 : o->normal.s0;
	o->normal.s1 = (o->normal.s1 < -1) ? -1 : o->normal.s1;
	o->normal.s2 = (o->normal.s2 < -1) ? -1 : o->normal.s2;
}

void	validation_cylinder(t_cylinder *o)
{
	o->origin.s0 = (o->origin.s0 > MAXF) ? MAXF : o->origin.s0;
	o->origin.s1 = (o->origin.s1 > MAXF) ? MAXF : o->origin.s1;
	o->origin.s2 = (o->origin.s2 > MAXF) ? MAXF : o->origin.s2;
	o->origin.s0 = (o->origin.s0 < MINF) ? MINF : o->origin.s0;
	o->origin.s1 = (o->origin.s1 < MINF) ? MINF : o->origin.s1;
	o->origin.s2 = (o->origin.s2 < MINF) ? MINF : o->origin.s2;
	o->normal.s0 = (o->normal.s0 > 1) ? 1 : o->normal.s0;
	o->normal.s1 = (o->normal.s1 > 1) ? 1 : o->normal.s1;
	o->normal.s2 = (o->normal.s2 > 1) ? 1 : o->normal.s2;
	o->normal.s0 = (o->normal.s0 < -1) ? -1 : o->normal.s0;
	o->normal.s1 = (o->normal.s1 < -1) ? -1 : o->normal.s1;
	o->normal.s2 = (o->normal.s2 < -1) ? -1 : o->normal.s2;
	if (o->radius > MAXF || o->radius < MINF)
	{
		ft_putendl_fd("Invalid radius of cylinder", 2);
		o->radius = 2;
		o->r2 = o->radius * o->radius;
	}
	if (o->height > MAXF || o->height < MINF)
	{
		ft_putendl_fd("Invalid height of cylinder", 2);
		o->height = 2;
	}
}

void	validation_cone2(t_cone *o)
{
	o->normal.s0 = (o->normal.s0 > 1) ? 1 : o->normal.s0;
	o->normal.s1 = (o->normal.s1 > 1) ? 1 : o->normal.s1;
	o->normal.s2 = (o->normal.s2 > 1) ? 1 : o->normal.s2;
	o->normal.s0 = (o->normal.s0 < -1) ? -1 : o->normal.s0;
	o->normal.s1 = (o->normal.s1 < -1) ? -1 : o->normal.s1;
	o->normal.s2 = (o->normal.s2 < -1) ? -1 : o->normal.s2;
	if (o->half_tangent > MAXF || o->half_tangent < 0)
	{
		ft_putendl_fd("Invalid half_tangent of cone", 2);
		o->half_tangent = 0.5;
	}
	if (o->m1 > MAXF || o->m1 < MINF)
	{
		ft_putendl_fd("Invalid m1 of cone", 2);
		o->m1 = 2;
	}
	if (o->m2 > MAXF || o->m2 < MINF)
	{
		ft_putendl_fd("Invalid m2 of cone", 2);
		o->m2 = 4;
	}
}

void	validation_cone(t_cone *o)
{
	if (o->origin.s0 > MAXF || o->origin.s0 < MINF ||
		o->origin.s1 > MAXF || o->origin.s1 < MINF ||
		o->origin.s2 > MAXF || o->origin.s2 < MINF)
	{
		ft_putendl_fd("ORIGIN of cone is invalid", 2);
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
		ft_putendl_fd("NORMAL of cone is invalid", 2);
	}
	validation_cone2(o);
}
