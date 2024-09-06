/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:03:43 by mdella-r          #+#    #+#             */
/*   Updated: 2024/09/06 10:47:16 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

static void	intersect_cylinder(t_coord pixel, t_cylinder cylinder, double t, t_ray ray, t_wdata *win_data)
{
	t_coord	int_point;
	t_coord	base_to_point;
	double	height_proj;

	int_point = vector_add(ray.origin, vector_scale(ray.direction, t));
	base_to_point = vector_subtract(int_point, cylinder.position);
	height_proj = vector_dot(base_to_point, cylinder.vector_norm);
	if (height_proj >= 0 && height_proj <= cylinder.height)
		put_pixel(win_data, pixel.x, pixel.y, cylinder.color);
}

void	render_cylinder(t_ray ray, t_cylinder cylinder, t_wdata *win_data, t_coord pixel)
{
	t_coord	center_adjust;
	t_index	id;
	double	t1;
	double	t2;
	double	t;

	center_adjust = vector_subtract(ray.origin, cylinder.position);
	id.i = vector_dot(ray.direction, ray.direction) - pow(vector_dot(ray.direction, cylinder.vector_norm), 2);
	id.j = 2.0 * (vector_dot(center_adjust, ray.direction) - (vector_dot(center_adjust, cylinder.vector_norm) * vector_dot(ray.direction, cylinder.vector_norm)));
	id.k =  vector_dot(center_adjust, center_adjust) - pow(vector_dot(center_adjust, cylinder.vector_norm), 2) - pow(cylinder.diameter /2, 2);
	id.t = id.j * id.j - 4 * id.i * id.j;
	if (id.t >=0)
	{
		t1 = (-id.j - sqrt(id.t)) / (2 * id.i);
		t2 = (-id.j + sqrt(id.t)) / (2 * id.i);
		if (t1 < t2)
			t = t1;
		else
			t = t2;
		if (t > 0)
			intersect_cylinder(pixel, cylinder, t, ray, win_data);
	}
}
