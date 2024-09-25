/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:53:26 by mdella-r          #+#    #+#             */
/*   Updated: 2024/09/25 15:02:43 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	render_sphere(t_ray ray, t_sphere sphere,
					t_wdata *win_data, t_coord pixel)
{
	double			t;
	t_coord			center_adjust;
	t_double		id;	

	center_adjust = subtract(ray.origin, sphere.position);
	id.a = dot(ray.direction, ray.direction);
	id.b = 2.0 * dot(center_adjust, ray.direction);
	id.c = dot(center_adjust, center_adjust) - pow(sphere.diameter / 2, 2);
	id.disc = pow(id.b, 2) - 4 * id.a * id.c;
	if (id.disc >= 0)
	{
		t = (-id.b - sqrt(id.disc)) / (2.0 * id.a);
		if (t > 0 && t < *closest_dist())
		{
			*closest_dist() = t;
			if (t < *sphere_dist())
				*sphere_dist() = t;
			put_pixel(win_data, pixel.x, pixel.y, sphere.color);
		}
	}
}
