/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:53:26 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/18 15:55:28 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	render_sphere(t_ray ray, t_sphere sphere, t_hit_record *rec)
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
		if (t > 0 && t < *closest_dist() && t < *sphere_dist())
		{
			*closest_dist() = t;
			*sphere_dist() = t;
			rec->t = t;
			rec->p = add(ray.origin, scale(ray.direction, t));
			rec->normal = norm(subtract(rec->p, sphere.position));
			rec->color = sphere.color;
			rec->hit = 1;
		}
	}
}
