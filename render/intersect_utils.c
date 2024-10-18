/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:38:06 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/18 16:15:44 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_double	get_coef_sphere(t_ray ray, t_sphere sphere)
{
	t_coord		oc;
	t_double	coef;

	oc = subtract(ray.origin, sphere.position);
	coef.a = dot(ray.direction, ray.direction);
	coef.b = 2.0 * dot(oc, ray.direction);
	coef.c = dot(oc, oc) - (sphere.diameter / 2) * (sphere.diameter / 2);
	coef.disc = coef.b * coef.b - 4 * coef.a * coef.c;
	return (coef);
}

static double	get_closest_dist(double t1, double t2)
{
	double	ret;

	ret = 0;
	if (t1 < t2)
		ret = t1;
	else
		ret = t2;
	if (ret < 0)
	{
		if (t1 < t2)
			ret = t2;
		else
			ret = t1;
	}
	return (ret);
}

int	intersect_sphere(t_ray ray, t_sphere sphere, t_hit_record *rec)
{
	t_double	coef;
	double		sqrt_discriminant;
	t_double	t;

	coef = get_coef_sphere(ray, sphere);
	if (coef.disc < 0)
		return (0);
	sqrt_discriminant = sqrt(coef.disc);
	t.a = (-coef.b - sqrt_discriminant) / (2 * coef.a);
	t.b = (-coef.b + sqrt_discriminant) / (2 * coef.a);
	t.c = get_closest_dist(t.a, t.b);
	if (t.c < 0)
		return (0);
	rec->t = t.c;
	rec->p = add(ray.origin, scale(ray.direction, t.c));
	rec->normal = norm(subtract(rec->p, sphere.position));
	rec->color = sphere.color;
	if (dot(ray.direction, rec->normal) > 0)
		rec->normal = scale(rec->normal, -1);
	return (1);
}
