

#include "rt.h"

char get_fig_type(char *s)
{
	if (!ft_strncmp("Sphere", s, 6))
		return (1);
	else if (!ft_strncmp("Plane", s, 5))
		return (2);
	else if (!ft_strncmp("Cylinder", s, 8))
		return (3);
	else if (!ft_strncmp("Cone", s, 4))
		return (4);
	else if (!ft_strncmp("Light", s, 5))
		return (0);
	else
		ft_error(MES5);
	return (127);
}

// union u_color get_fig_col(char *s)
// {
// 	union u_color   col;
// 	if (ft_strlen(s) < 7)
// 		ft_error(MES2);
// 	col.channels[0] = (ft_atoi(s) <= 255) ? ft_atoi(s) : 255;
// 	col.channels[1] = ft_atoi(s = ft_strchr(s,',') + 1);
// 	col.channels[2] = ft_atoi(s = ft_strchr(s,',') + 1);
// 	col.channels[3] = ft_atoi(ft_strchr(s,',') + 1);
// 	return (col);
// }

// double ft_atof(const char* s)
// {
// 	double rez = 0;
// 	int fact = 1;
// 	if (*s == '-')
// 	{
// 		s++;
// 		fact = -1;
// 	}
// 	for (int point_seen = 0; *s; s++){
// 		if (*s == '.'){
// 			point_seen = 1;
// 			continue;
// 		};
// 		int d = *s - '0';
// 		if (d >= 0 && d <= 9){
// 			if (point_seen) fact /= 10.0f;
// 			rez = rez * 10.0f + (float)d;
// 		};
// 	};
// 	return rez * fact;
// }

// t_vec		get_fig_pos(char *s)
// {
// 	t_vec   pos;
// 	if (ft_strlen(s) < 8)
// 		ft_error(MES2);
// 	pos[0] = ft_atoi(s);
// 	pos[1] = ft_atoi(s = ft_strchr(s,',') + 1);
// 	pos[2] = ft_atoi(ft_strchr(s,',') + 1);
// 	return (pos);
// }
