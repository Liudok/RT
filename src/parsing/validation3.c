/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 14:01:59 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/12 14:02:02 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	validation_disk(t_disk *o)
{
	if (o->origin.s0 > MAXF || o->origin.s0 < MINF ||
		o->origin.s1 > MAXF || o->origin.s1 < MINF ||
		o->origin.s2 > MAXF || o->origin.s2 < MINF)
	{
		ft_putendl_fd("ORIGIN of disk is invalid", 2);
	}
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
	o->normal.s1 = (o->normal.s1 < -1) ? 1 : o->normal.s1;
	o->normal.s2 = (o->normal.s2 < -1) ? -1 : o->normal.s2;
	if (o->radius2 > MAXF || o->radius2 < MINF)
	{
		ft_putendl_fd("Invalid radius of disk", 2);
		o->radius2 = 5;
	}
}

void 	validation_torus(t_torus *o)
{
	if (o->origin.s0 > MAXF || o->origin.s0 < MINF ||
		o->origin.s1 > MAXF || o->origin.s1 < MINF ||
		o->origin.s2 > MAXF || o->origin.s2 < MINF)
	{
		ft_putendl_fd("ORIGIN of torus is invalid", 2);
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
		ft_putendl_fd("NORMAL of torus is invalid", 2);
	}
	o->normal.s0 = (o->normal.s0 > 1) ? 1 : o->normal.s0;
	o->normal.s1 = (o->normal.s1 > 1) ? 1 : o->normal.s1;
	o->normal.s2 = (o->normal.s2 > 1) ? 1 : o->normal.s2;
	o->normal.s0 = (o->normal.s0 < -1) ? -1 : o->normal.s0;
	o->normal.s1 = (o->normal.s1 < -1) ? -1 : o->normal.s1;
	o->normal.s2 = (o->normal.s2 < -1) ? -1 : o->normal.s2;
	if (o->big_radius2 > MAXF || o->big_radius2 < MINF)
	{
		ft_putendl_fd("Invalid radius of torus", 2);
		o->big_radius2 = 5;
	}
	if (o->small_radius2 > MAXF || o->small_radius2 < MINF)
	{
		ft_putendl_fd("Invalid radius of torus", 2);
		o->small_radius2 = 5;
	}
}

void 	validation_triangle(t_triangle *o)
{
	if (o->vertex0.s0 > MAXF || o->vertex0.s0 < MINF ||
		o->vertex0.s1 > MAXF || o->vertex0.s1 < MINF ||
		o->vertex0.s2 > MAXF || o->vertex0.s2 < MINF ||
		o->vertex1.s0 > MAXF || o->vertex1.s0 < MINF ||
		o->vertex1.s1 > MAXF || o->vertex1.s1 < MINF ||
		o->vertex1.s2 > MAXF || o->vertex1.s2 < MINF ||
		o->vertex2.s0 > MAXF || o->vertex2.s0 < MINF ||
		o->vertex2.s1 > MAXF || o->vertex2.s1 < MINF ||
		o->vertex2.s2 > MAXF || o->vertex2.s2 < MINF)
	{
		ft_putendl_fd("triangle is invalid", 2);
	}
	o->vertex0.s0 = (o->vertex0.s0 > MAXF) ? MAXF : o->vertex0.s0;
	o->vertex0.s1 = (o->vertex0.s1 > MAXF) ? MAXF : o->vertex0.s1;
	o->vertex0.s2 = (o->vertex0.s2 > MAXF) ? MAXF : o->vertex0.s2;
	o->vertex0.s0 = (o->vertex0.s0 < MINF) ? MINF : o->vertex0.s0;
	o->vertex0.s1 = (o->vertex0.s1 < MINF) ? MINF : o->vertex0.s1;
	o->vertex0.s2 = (o->vertex0.s2 < MINF) ? MINF : o->vertex0.s2;
	o->vertex1.s0 = (o->vertex1.s0 > MAXF) ? MAXF : o->vertex1.s0;
	o->vertex1.s1 = (o->vertex1.s1 > MAXF) ? MAXF : o->vertex1.s1;
	o->vertex1.s2 = (o->vertex1.s2 > MAXF) ? MAXF : o->vertex1.s2;
	o->vertex1.s0 = (o->vertex1.s0 < MINF) ? MINF : o->vertex1.s0;
	o->vertex1.s1 = (o->vertex1.s1 < MINF) ? MINF : o->vertex1.s1;
	o->vertex1.s2 = (o->vertex1.s2 < MINF) ? MINF : o->vertex1.s2;
	o->vertex2.s0 = (o->vertex2.s0 > MAXF) ? MAXF : o->vertex2.s0;
	o->vertex2.s1 = (o->vertex2.s1 > MAXF) ? MAXF : o->vertex2.s1;
	o->vertex2.s2 = (o->vertex2.s2 > MAXF) ? MAXF : o->vertex2.s2;
	o->vertex2.s0 = (o->vertex2.s0 < MINF) ? MINF : o->vertex2.s0;
	o->vertex2.s1 = (o->vertex2.s1 < MINF) ? MINF : o->vertex2.s1;
	o->vertex2.s2 = (o->vertex2.s2 < MINF) ? MINF : o->vertex2.s2;

}