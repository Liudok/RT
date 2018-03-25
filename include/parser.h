/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:44:49 by lberezyn          #+#    #+#             */
/*   Updated: 2018/03/07 17:44:51 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct	s_olist
{
    char        type;
    int         flag;
    int         vertexes;
    int         normals;
    int         f;
    cl_uchar4   col;
    double  pos[3];
    struct s_olist *next;
}               t_olist;
//typedef struct	s_object
//{
//	cl_int		type;
//	cl_int		material;
//	cl_int		albedo_n;
//	cl_int		tex_scale;
//	VEC3		emission;
//	VEC3		dir;
//	VEC3		point1;
//	VEC3		point2;
//	VEC3		point3;
//	VEC3		n;
//	VEC3		edge0;
//	VEC3		edge1;
//	VEC3		edge2;
//	VEC3		color;
//	VEC3		absorption;
//	VEC3		upsilon;
//	VEC3		a;
//	VEC3		b;
//	VEC3		c;
//	cl_float	radius;
//	cl_float	radius2;
//	cl_float	bot;
//	cl_float	top;
//	cl_float	k;
//	cl_float	c2;
//	cl_float	glossiness;
//	cl_float	kd;
//	cl_float	refr_index;
//	cl_float	tex_shift;
//	cl_int		period;
//	cl_int		frequency;
//}				t_object;

/*
 * PARSING FUNCTIONS
 *
 */
//void ft_parser(t_gra *o, char *file_name);
char get_fig_type(char *s);
void safe_color(t_olist *list, char *s, int flag);
void figs_center(t_olist *list, char *s, int flag);
#endif
