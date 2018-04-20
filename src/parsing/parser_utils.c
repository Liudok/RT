
# include "../../libJSON/include/json.h"
#include "../../include/rt.h"

float		get_number(json_value *value)
{
	float ret;

	ret = 0;
	if (value->type == json_integer)
		ret = (float)value->u.integer;
	else if (value->type == json_double)
		ret = (float)value->u.dbl;
	else
		ft_error("Not a number format where expected.");
	return (ret);
}

float3			get_float3(json_value *value)
{
	float3		ret;

	ret = (float3){{0, 0, 0}};
	if (value == NULL)
		ft_error("No value for float3.");
	ret.s0 = get_number(value->u.array.values[0]);
	ret.s1 = get_number(value->u.array.values[1]);
	ret.s2 = get_number(value->u.array.values[2]);
	printf("color: %f\t%f\t%f\n", ret.s0,ret.s1,ret.s2);
	return (ret);
}

float4			get_float4(json_value *value)
{
	float4		ret;

	ret = (float4){{0, 0, 0, 0}};
	if (value == NULL)
		ft_error("No value for float4.");
	ret.s0 = get_number(value->u.array.values[0]);
	ret.s1 = get_number(value->u.array.values[1]);
	ret.s2 = get_number(value->u.array.values[2]);
	ret.s3 = get_number(value->u.array.values[3]);
	printf("float4: %f\t%f\t%f\t%f\n", ret.s0,ret.s1,ret.s2,ret.s3);
	if (ret.s0 > 1 || ret.s0 < 0 || ret.s1 > 1 || ret.s1 < 0 ||
			ret.s2 > 1 || ret.s2 < 0 || ret.s3 > 1 || ret.s3 < 0)
		ft_error("The value in material can not be more than 1 or less than 0.");
	return (ret);
}

t_obj_type		get_type(json_value *value)
{
	if (value->type != json_string)
		ft_error("Not valid json type.");
	if (!ft_strncmp(value->u.string.ptr, "plane", 5))
		return (plane);
	else if (!ft_strncmp(value->u.string.ptr, "sphere", 6))
		return (sphere);
	else if (!ft_strncmp(value->u.string.ptr, "cylinder", 8))
		return (cylinder);
	else if (!ft_strncmp(value->u.string.ptr, "cone", 4))
		return (cone);
	ft_error("Not valid object type.");
	return (not_valid);
}

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
