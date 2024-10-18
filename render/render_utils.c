/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:07:31 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/18 17:10:06 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_coord	random_in_unit_disk(void)
{
	t_coord	p;

	while (dot(p, p) >= 1.0)
	{
		p = (t_coord){
			2.0 * ((double)rand() / RAND_MAX) - 1.0,
			2.0 * ((double)rand() / RAND_MAX) - 1.0,
			0
		};
	}
	return (p);
}

t_coord	random_in_hemisphere(t_coord normal)
{
	t_coord	in_unit_sphere;

	in_unit_sphere = (t_coord){0, 0, 0};
	while (dot(in_unit_sphere, in_unit_sphere) >= 1.0)
	{
		in_unit_sphere = (t_coord){
			2.0 * ((double)rand() / RAND_MAX) - 1.0,
			2.0 * ((double)rand() / RAND_MAX) - 1.0,
			2.0 * ((double)rand() / RAND_MAX) - 1.0
		};
	}
	if (dot(in_unit_sphere, normal) > 0.0)
		return (in_unit_sphere);
	else
		return (scale(in_unit_sphere, -1));
}

t_rgb	color_check( t_rgb color)
{
	if (color.x > 255)
		color.x = 255;
	if (color.y > 255)
		color.y = 255;
	if (color.z > 255)
		color.z = 255;
	return (color);
}

t_coord	get_cap_center(int i, t_cylinder cylinder, t_coord axis)
{
	t_coord	cap_center;

	if (i == 0)
		cap_center = add(cylinder.position,
				scale(axis, -1 * (cylinder.height / 2)));
	else
		cap_center = add(cylinder.position,
				scale(axis, cylinder.height / 2));
	return (cap_center);
}

void	get_cap_norm(int i, t_coord *cap_normal, t_coord axis)
{
	if (i == 0)
		*cap_normal = scale(axis, -1);
	else
		*cap_normal = axis;
}
