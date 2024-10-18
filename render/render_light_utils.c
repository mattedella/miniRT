/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_light_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:29:46 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/18 16:35:10 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_double	calculate_cylinder_coefficients(t_ray ray, t_cylinder cylinder,
		t_coord axis, t_coord oc)
{
	t_double	coeffs;

	coeffs.a = dot(ray.direction, ray.direction)
		- pow(dot(ray.direction, axis), 2);
	coeffs.b = 2 * (dot(ray.direction, oc)
			- dot(ray.direction, axis) * dot(oc, axis));
	coeffs.c = dot(oc, oc) - pow(dot(oc, axis), 2)
		- pow(cylinder.diameter / 2, 2);
	return (coeffs);
}

int	solve_quadratic(t_double *coeffs, t_double *t)
{
	double	discriminant;
	double	sqrt_discriminant;
	double	temp;

	discriminant = coeffs->b * coeffs->b - 4 * coeffs->a * coeffs->c;
	if (discriminant < 0)
		return (0);
	sqrt_discriminant = sqrt(discriminant);
	t->a = (-coeffs->b - sqrt_discriminant) / (2 * coeffs->a);
	t->b = (-coeffs->b + sqrt_discriminant) / (2 * coeffs->a);
	if (t->a > t->b)
	{
		temp = t->a;
		t->a = t->b;
		t->b = temp;
	}
	return (1);
}

double	intersect_cylinder_body(t_ray ray, t_cylinder cylinder,
		t_coord axis, t_double *t)
{
	t_coord	hit_point;
	t_coord	center_to_hit;
	double	half_height;

	half_height = cylinder.height / 2;
	if (t->a >= 0)
	{
		hit_point = add(ray.origin, scale(ray.direction, t->a));
		center_to_hit = subtract(hit_point, cylinder.position);
		if (fabs(dot(center_to_hit, axis)) <= half_height)
			return (t->a);
	}
	else if (t->b >= 0)
	{
		hit_point = add(ray.origin, scale(ray.direction, t->b));
		center_to_hit = subtract(hit_point, cylinder.position);
		if (fabs(dot(center_to_hit, axis)) <= half_height)
			return (t->b);
	}
	return (-1);
}

t_hit_record	set_hit_record(t_ray ray, double t,
		t_coord normal, t_rgb color)
{
	t_hit_record	rec;

	*closest_dist() = t;
	*cylinder_dist() = t;
	rec.t = t;
	rec.p = add(ray.origin, scale(ray.direction, t));
	rec.normal = normal;
	rec.color = color;
	rec.hit = 1;
	return (rec);
}

t_coord	calculate_body_normal(t_ray ray, t_cylinder cylinder,
		t_coord axis, double t)
{
	t_coord	hit_point;
	t_coord	center_to_hit;
	t_coord	radial_vector;

	hit_point = add(ray.origin, scale(ray.direction, t));
	center_to_hit = subtract(hit_point, cylinder.position);
	radial_vector = subtract(center_to_hit, scale(axis,
				dot(center_to_hit, axis)));
	return (norm(radial_vector));
}
