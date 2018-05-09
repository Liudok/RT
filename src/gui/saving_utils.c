
#include "../../include/panels.h"

void		print_prim_info2(int fd, t_object *o, int i)
{
	if (o[i].type == 3)
	{
		dprintf(fd,"\t\t\t\"origin\": [%f, %f, %f],\n", o[i].prim.cone.origin.s0, o[i].prim.cone.origin.s1, o[i].prim.cone.origin.s2);
		dprintf(fd,"\t\t\t\"normal\": [%f, %f, %f],\n", o[i].prim.cone.normal.s0, o[i].prim.cone.normal.s1, o[i].prim.cone.normal.s2);
		dprintf(fd,"\t\t\t\"half_tangent\": %f,\n", o[i].prim.cone.half_tangent);
		dprintf(fd,"\t\t\t\"m1\": %f,\n", o[i].prim.cone.m1);
		dprintf(fd,"\t\t\t\"m2\": %f,\n", o[i].prim.cone.m2);
	}
	else if (o[i].type == 4)
	{
		dprintf(fd,"\t\t\t\"origin\": [%f, %f, %f],\n", o[i].prim.disk.origin.s0, o[i].prim.disk.origin.s1, o[i].prim.disk.origin.s2);
		dprintf(fd,"\t\t\t\"normal\": [%f, %f, %f],\n", o[i].prim.disk.normal.s0, o[i].prim.disk.normal.s1, o[i].prim.disk.normal.s2);
		dprintf(fd,"\t\t\t\"radius2\": %f,\n", o[i].prim.disk.radius2);
	}
	else if (o[i].type == 5)
	{
		dprintf(fd,"\t\t\t\"origin\": [%f, %f, %f],\n", o[i].prim.torus.origin.s0, o[i].prim.torus.origin.s1, o[i].prim.torus.origin.s2);
		dprintf(fd,"\t\t\t\"normal\": [%f, %f, %f],\n", o[i].prim.torus.normal.s0, o[i].prim.torus.normal.s1, o[i].prim.torus.normal.s2);
		dprintf(fd,"\t\t\t\"big_radius2\": %f,\n", o[i].prim.torus.big_radius2);
		dprintf(fd,"\t\t\t\"small_radius2\": %f,\n", o[i].prim.torus.small_radius2);
	}
}

void		print_prim_info(int fd, t_object *o, int i)
{
	if (o[i].type == 0)
	{
		dprintf(fd,"\t\t\t\"origin\": [%f, %f, %f],\n", o[i].prim.sphere.origin.s0, o[i].prim.sphere.origin.s1, o[i].prim.sphere.origin.s2);
		dprintf(fd,"\t\t\t\"radius\": %f,\n", o[i].prim.sphere.radius);
	}
	else if (o[i].type == 1)
	{
		dprintf(fd,"\t\t\t\"origin\": [%f, %f, %f],\n", o[i].prim.plane.origin.s0, o[i].prim.plane.origin.s1, o[i].prim.plane.origin.s2);
		dprintf(fd,"\t\t\t\"normal\": [%f, %f, %f],\n", o[i].prim.plane.normal.s0, o[i].prim.plane.normal.s1, o[i].prim.plane.normal.s2);
	}
	else if (o[i].type == 2)
	{
		dprintf(fd,"\t\t\t\"origin\": [%f, %f, %f],\n", o[i].prim.cylinder.origin.s0, o[i].prim.cylinder.origin.s1, o[i].prim.cylinder.origin.s2);
		dprintf(fd,"\t\t\t\"normal\": [%f, %f, %f],\n", o[i].prim.cylinder.normal.s0, o[i].prim.cylinder.normal.s1, o[i].prim.cylinder.normal.s2);
		dprintf(fd,"\t\t\t\"radius\": %f,\n", o[i].prim.cylinder.radius);
		dprintf(fd,"\t\t\t\"height\": %f,\n", o[i].prim.cylinder.height);
	}
	else
		print_prim_info2(fd, o, i);
}

char 		*type_to_str(int n)
{
	if (n == 0)
		return ("sphere");
	else if (n == 1)
		return ("plane");
	else if (n == 2)
		return ("cylinder");
	else if (n == 3)
		return ("cone");
	else if (n == 4)
		return ("disk");
	else if (n == 5)
		return ("torus");
	else if (n == 6)
		return ("triangle");
	else if (n == 7)
		return ("mobius");
	else if (n == 8)
		return ("bool_substraction");
	else if (n == 9)
		return ("bool_intersection");
	else if (n == 10)
		return ("cube");
	else if (n == 11)
		return ("parabaloid");
	else if (n == 12)
		return ("julia");
	else
		return ("not_valid");
}
