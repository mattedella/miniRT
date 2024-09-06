/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:53:26 by mdella-r          #+#    #+#             */
/*   Updated: 2024/09/06 10:12:32 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

static int	 intersect_ray_sphere(t_ray ray, t_sphere sphere, double *t)
{
	t_coord	center_adjust;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	center_adjust = vector_subtract(ray.origin, sphere.position);
	a = vector_dot(ray.direction, ray.direction);
	b = 2.0 * vector_dot(center_adjust, ray.direction);
	c =  vector_dot(center_adjust, center_adjust) - pow(sphere.diameter /2, 2);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return 0;
	else
	{
		*t = (-b - sqrt(discriminant)) / (2.0 * a);
		return 1;
	}
}

void	render_sphere(t_ray ray, t_sphere sphere, t_wdata *win_data, t_coord pixel)
{
	double	t;
	// t_rgb	color;

	// color = (t_rgb){0, 0, 0};
	if (intersect_ray_sphere(ray, sphere, &t))
		put_pixel(win_data, pixel.x, pixel.y, sphere.color);
	// else
	// {
	// 	if (pixel.y < WIN_HEIGHT / 2)
	// 		put_pixel(win_data, pixel.x, pixel.y, color);
	// 	else
	// 	{
	// 		color = (t_rgb){10, 10, 10};
	// 		put_pixel(win_data, pixel.x, pixel.y, color);
	// 	}
	// }
	
}
