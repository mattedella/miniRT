/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:03:43 by mdella-r          #+#    #+#             */
/*   Updated: 2024/09/25 15:02:46 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	intersect_cylinder(t_coord pixel, t_cylinder cylinder,
							t_coord hit_point, t_wdata *win_data)
{
	t_coord	base_to_point;
	double	height_proj;

	base_to_point = subtract(hit_point, cylinder.position);
	height_proj = dot(base_to_point, cylinder.vector_norm);
	if (height_proj >= 0 && height_proj <= cylinder.height)
		put_pixel(win_data, pixel.x, pixel.y, cylinder.color);
}

static t_double	get_discriminant(t_ray ray, t_cylinder cylinder, t_coord c_adj)
{
	t_double	ret;

	ret.a = dot(ray.direction, ray.direction)
		- pow(dot(ray.direction, cylinder.vector_norm), 2);
	ret.b = 2.0 * (dot(c_adj, ray.direction)
			- (dot(c_adj, cylinder.vector_norm)
				* dot(ray.direction, cylinder.vector_norm)));
	ret.c = dot(c_adj, c_adj)
		- pow(dot(c_adj, cylinder.vector_norm), 2)
		- pow(cylinder.diameter / 2, 2);
	ret.disc = ret.b * ret.b - 4 * ret.a * ret.c;
	return (ret);
}

void	render_cylinder(t_ray ray, t_cylinder cylinder,
						t_wdata *win_data, t_coord pixel)
{
	t_coord		center_adjust;
	t_double	id;
	t_double	t;
	t_coord		hit_point;

	center_adjust = subtract(ray.origin, cylinder.position);
	id = get_discriminant(ray, cylinder, center_adjust);
	if (id.disc >= 0)
	{
		t.a = (-id.b - sqrt(id.disc)) / (2 * id.a);
		t.b = (-id.b + sqrt(id.disc)) / (2 * id.a);
		if (t.a < t.b)
			t.disc = t.a;
		else
			t.disc = t.b;
		if (t.disc > 0 && t.disc < *closest_dist())
		{
			*closest_dist() = t.disc;
			if (t.disc < *cylinder_dist())
				*cylinder_dist() = t.disc;
			hit_point = add(ray.origin, scale(ray.direction, t.disc));
			intersect_cylinder(pixel, cylinder, hit_point, win_data);
		}
	}
}
