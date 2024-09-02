#include "miniRT.h"

t_coord	vector_add(t_coord v1, t_coord v2)
{
	t_coord result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_coord	vector_subtract(t_coord v1, t_coord v2)
{
	t_coord result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_coord	vector_scale(t_coord v, double t)
{
	t_coord result;

	result.x = v.x * t;
	result.y = v.y * t;
	result.z = v.z * t;
	return (result);
}

unsigned int	create_rgb(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}
