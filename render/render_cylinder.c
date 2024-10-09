/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:03:43 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/09 13:59:40 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_double	get_vars(t_ray ray, t_cylinder cylinder)
{
	t_coord		dir_perp;
	t_coord		oc_perp;
	t_coord		oc;
	t_double	vars;

	oc = subtract(ray.origin, cylinder.position);
	dir_perp = subtract(ray.direction, scale(cylinder.vector_norm,
			dot(ray.direction, cylinder.vector_norm)));
	oc_perp = subtract(oc, scale(cylinder.vector_norm,
			dot(oc, cylinder.vector_norm)));
	vars.a = dot(dir_perp, dir_perp);
	vars.b = 2.0 * dot(oc_perp, dir_perp);
	vars.c = dot(oc_perp, oc_perp) - pow(cylinder.diameter / 2, 2);
	vars.disc = pow(vars.b, 2) - (4 * vars.a * vars.c);
	return (vars);
}

static int within_cylinder_height(t_cylinder cylinder, t_coord point)
{
	double hit_height;
	double half_height;

	hit_height = dot(subtract(point, cylinder.position), cylinder.vector_norm);
	half_height = cylinder.height / 2;
	if (hit_height < -half_height || hit_height > half_height)
		return (0);
	else
		return (1);
}

void	render_cylinder(t_ray ray, t_cylinder cylinder,
						t_wdata *win_data, t_coord pixel)
{
	t_coord		point;
    t_double	vars;
	t_double	dist;

	vars = get_vars(ray, cylinder);
	if (vars.disc < 0)
		return ;
	dist.a = (-vars.b - sqrt(vars.disc)) / (2 * vars.a);
	dist.b = (-vars.b + sqrt(vars.disc)) / (2 * vars.a);
	dist.c = fmin(dist.a, dist.b);
	point = add(ray.origin, scale(ray.direction, dist.c));
	if (dist.c > 0 && dist.c < *closest_dist()  && dist.c < *cylinder_dist()
		&& within_cylinder_height(cylinder, point))
	{
		*closest_dist() = dist.c;
		*cylinder_dist() = dist.c;
		put_pixel(win_data, (int)pixel.x, (int)pixel.y, cylinder.color);
	}
}
