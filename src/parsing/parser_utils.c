
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

int2			get_int2(json_value *value)
{
	int2		ret;

	ret = (int2){{0, 0}};
	if (value == NULL)
		ft_error("No value for int2.");
	ret.s0 = (int)get_number(value->u.array.values[0]);
	ret.s1 = (int)get_number(value->u.array.values[1]);
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
	else if (!ft_strncmp(value->u.string.ptr, "bool_substraction", 17))
		return (bool_substraction);
	else if (!ft_strncmp(value->u.string.ptr, "bool_intersection", 17))
		return (bool_intersection);
	ft_error("Not valid object type.");
	return (not_valid);
}
