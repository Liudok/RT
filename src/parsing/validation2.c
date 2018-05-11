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

//void 	validation_sphere(t_sphere *o)
//{
//	if (o->origin.s0 > MAXF || o->origin.s0 < MINF ||
//		o->origin.s1 > MAXF || o->origin.s1 < MINF ||
//		o->origin.s2 > MAXF || o->origin.s2 < MINF)
//	{
//		ft_putendl_fd("ORIGIN of sphere is invalid", 2);
//	}
//	o->origin.s0 = (o->origin.s0 > MAXF) ? MAXF : o->origin.s0;
//	o->origin.s1 = (o->origin.s1 > MAXF) ? MAXF : o->origin.s1;
//	o->origin.s2 = (o->origin.s2 > MAXF) ? MAXF : o->origin.s2;
//	o->origin.s0 = (o->origin.s0 < MINF) ? MINF : o->origin.s0;
//	o->origin.s1 = (o->origin.s1 < MINF) ? MINF : o->origin.s1;
//	o->origin.s2 = (o->origin.s2 < MINF) ? MINF : o->origin.s2;
//	if (o->radius > MAXF || o->radius < MINF)
//	{
//		ft_putendl_fd("Invalid radius of sphere", 2);
//		o->radius = 5;
//		o->r2 = o->radius * o->radius;
//	}
//}
