/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:44:49 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/11 15:11:23 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libJSON/include/json.h"
# include "panels.h"
# include "kernel.h"

float4			get_float4(json_value *value);
t_material		get_material(json_value *value);
float			get_number(json_value *value);
float3			get_float3(json_value *value);
int2			get_int2(json_value *value);
uchar4			get_uchar4(json_value *value);
t_obj_type		get_type(json_value *value);
void			get_objects_details(t_object *o, char *n,
					struct _json_value *val);
void			get_primitives_details(t_object *o, char *n,
					struct _json_value *val);
void			get_primitives_details2(t_object *o, char *n,
					struct _json_value *val);
void			parse_camera(json_value *value, t_scene *s);
void			get_primitives_details(t_object *o, char *n, struct _json_value *val);
void			get_primitives_details2(t_object *o, char *n, struct _json_value *val);
void			get_primitives_details3(t_object *o, char *n, struct _json_value *val);
void			get_primitives_details4(t_object *o, char *n, struct _json_value *val);
void			get_primitives_details5(t_object *o, char *n, struct _json_value *val);
int 			validation(t_object *o);
void 			validation_sphere(t_sphere *o);
void 			validation_plane(t_plane *o);
void 			validation_cylinder(t_cylinder *o);
void 			validation_cone(t_cone *o);
void 			validation_disk(t_disk *o);
void 			validation_torus(t_torus *o);
void 			validation_triangle(t_triangle *o);
void 			validation_mobius(t_mobius *o);
void 			validation_cube(t_cube *o);
void 			validation_parabaloid(t_parabaloid *o);
void 			validation_julia(t_julia *o);

#endif
