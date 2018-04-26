/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:44:49 by lberezyn          #+#    #+#             */
/*   Updated: 2018/04/25 12:44:19 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libJSON/include/json.h"
# include "panels.h"
# include "kernel.h"

float4			get_float4(json_value *value);
float			get_number(json_value *value);
float3			get_float3(json_value *value);
int2			get_int2(json_value *value);
t_obj_type		get_type(json_value *value);
void			get_objects_details(t_object *o, char *n, struct _json_value *val);
void			get_primitives_details(t_object *o, char *n, struct _json_value *val);
void			get_primitives_details2(t_object *o, char *n, struct _json_value *val);
void			parse_camera(json_value *value, t_scene *s);

#endif
