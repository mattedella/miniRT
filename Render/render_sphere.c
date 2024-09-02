/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:53:26 by mdella-r          #+#    #+#             */
/*   Updated: 2024/09/02 17:44:52 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

static int	 intersect_ray_sphere(t_ray ray, t_sphere sphere, double *t)
{
	t_coord	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vector_subtract(ray.origin, sphere.position);
	a = vector_dot(ray.direction, ray.direction);
	b = 2.0 * vector_dot(oc, ray.direction);
	c = vector_dot(oc, oc) - (sphere.diameter / 2) * (sphere.diameter / 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return 0;
	else
	{
		*t = (-b - sqrt(discriminant)) / (2.0 * a);
		return 1;
	}
}

void	render_sphere(t_ray ray, t_sphere sphere, t_wdata *win_data)
{
	double	t;
	// t_rgb	color;

	(void)win_data;
	if (intersect_ray_sphere(ray, sphere, &t))
	{
		printf("SI! sfera colpita\n");
		// color = sphere.color;
	}
	else
	{
		printf("NO! sfera non colpita\n");
		// color = (t_rgb){0, 0, 0};
	}
	// put_pixel(win_data, ray.direction.x, ray.direction.y, color);
}