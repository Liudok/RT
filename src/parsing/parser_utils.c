
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
	{
		ft_putendl_fd("Not a number format where expected", 2);
		g_error_flag = 1;
	}
	return (ret);
}

int2			get_int2(json_value *value)
{
	int2		ret;

	ret = (int2){{0, 0}};
	if (value == NULL || value->type != json_array || value->u.array.length != 2)
	{
		ft_putendl_fd("No value for int2.", 2);
		g_error_flag = 1;
		return (ret);
	}
	ret.s0 = (int)get_number(value->u.array.values[0]);
	ret.s1 = (int)get_number(value->u.array.values[1]);
	return (ret);
}

float3			get_float3(json_value *value)
{
	float3		ret;

	ret = (float3){{0, 0, 0}};
	if (value == NULL || value->type != json_array || value->u.array.length != 3)
	{
		ft_putendl_fd("No value for float3.", 2);
		g_error_flag = 1;
		return (ret);
	}
	ret.s0 = get_number(value->u.array.values[0]);
	ret.s1 = get_number(value->u.array.values[1]);
	ret.s2 = get_number(value->u.array.values[2]);
	return (ret);
}

uchar4			get_uchar4(json_value *value)
{
	uchar4		ret;

	ret = (uchar4){{0, 0, 0, 0}};
	if (value == NULL || value->type != json_array || value->u.array.length != 4)
	{
		ft_putendl_fd("No value for uchar4.", 2);
//		g_error_flag = 1;
		return (ret);
	}
	ret.s0 = get_number(value->u.array.values[0]);
	ret.s1 = get_number(value->u.array.values[1]);
	ret.s2 = get_number(value->u.array.values[2]);
	ret.s3 = get_number(value->u.array.values[3]);
	return (ret);
}

t_material		get_material(json_value *value)
{
	if (value->type != json_string)
	{
		ft_putendl_fd("Not valid json type..", 2);
//		g_error_flag = 1;
		return (diffuse);
	}
	if (!ft_strcmp(value->u.string.ptr, "diffuse"))
		return (diffuse);
	else if (!ft_strcmp(value->u.string.ptr, "specular"))
		return (specular);
	else if (!ft_strcmp(value->u.string.ptr, "glass"))
		return (glass);
	else if (!ft_strcmp(value->u.string.ptr, "emission"))
		return (emission);
	else if (!ft_strcmp(value->u.string.ptr, "transparent"))
		return (transparent);
	else
		return (diffuse);
}

float4			get_float4(json_value *value)
{
	float4		ret;

	ret = (float4){{0, 0, 0, 0}};
	if (value == NULL || value->type != json_array || value->u.array.length != 4)
		ft_error("No value for float4.");
	ret.s0 = get_number(value->u.array.values[0]);
	ret.s1 = get_number(value->u.array.values[1]);
	ret.s2 = get_number(value->u.array.values[2]);
	ret.s3 = get_number(value->u.array.values[3]);
	if (ret.s0 > 1 || ret.s0 < 0 || ret.s1 > 1 || ret.s1 < 0 ||
			ret.s2 > 1 || ret.s2 < 0 || ret.s3 > 1 || ret.s3 < 0)
	{
		ft_putendl_fd("The value in material can not be more than 1 or less than 0", 2);
		return (ret);
	}
	return (ret);
}

t_obj_type		get_type(json_value *value)
{
	if (value->type != json_string)
	{
		ft_putendl_fd("Not valid json type", 2);
		g_error_flag = 1;
		return (not_valid);
	}
	if (!ft_strncmp(value->u.string.ptr, "plane", 5))
		return (plane);
	else if (!ft_strncmp(value->u.string.ptr, "sphere", 6))
		return (sphere);
	else if (!ft_strncmp(value->u.string.ptr, "cylinder", 8))
		return (cylinder);
	else if (!ft_strncmp(value->u.string.ptr, "cone", 4))
		return (cone);
	else if (!ft_strncmp(value->u.string.ptr, "disk", 4))
		return (disk);
	else if (!ft_strncmp(value->u.string.ptr, "torus", 5))
		return (torus);
	else if (!ft_strncmp(value->u.string.ptr, "mobius", 6))
		return (mobius);
	else if (!ft_strncmp(value->u.string.ptr, "triangle", 8))
		return (triangle);
	else if (!ft_strncmp(value->u.string.ptr, "cube", 4))
		return (cube);
	else if (!ft_strncmp(value->u.string.ptr, "parabaloid", 10))
		return (parabaloid);
	else if (!ft_strncmp(value->u.string.ptr, "bool_substraction", 17))
		return (bool_substraction);
	else if (!ft_strncmp(value->u.string.ptr, "bool_intersection", 17))
		return (bool_intersection);
	else if (!ft_strncmp(value->u.string.ptr, "julia", 5))
		return (julia);
	ft_putendl_fd("Not valid object type", 2);
	g_error_flag = 1;
	return (not_valid);
}
