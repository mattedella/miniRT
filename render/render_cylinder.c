/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:03:43 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/16 14:07:28 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	calculate_cylinder_coefficients(t_ray ray, t_cylinder cylinder,
		t_coord axis, t_coord oc, t_double *coeffs)
{
	coeffs->a = dot(ray.direction, ray.direction)
		- pow(dot(ray.direction, axis), 2);
	coeffs->b = 2 * (dot(ray.direction, oc)
			- dot(ray.direction, axis) * dot(oc, axis));
	coeffs->c = dot(oc, oc) - pow(dot(oc, axis), 2)
		- pow(cylinder.diameter / 2, 2);
}

static int	solve_quadratic(t_double *coeffs, t_double *t)
{
	double	discriminant;
	double	sqrt_discriminant;

	discriminant = coeffs->b * coeffs->b - 4 * coeffs->a * coeffs->c;
	if (discriminant < 0)
		return (0);
	sqrt_discriminant = sqrt(discriminant);
	t->a = (-coeffs->b - sqrt_discriminant) / (2 * coeffs->a);
	t->b = (-coeffs->b + sqrt_discriminant) / (2 * coeffs->a);
	if (t->a > t->b)
	{
		double temp = t->a;
		t->a = t->b;
		t->b = temp;
	}
	return (1);
}

static double	intersect_cylinder_body(t_ray ray, t_cylinder cylinder,
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

static double	intersect_cylinder_cap(t_ray ray, t_cylinder cylinder,
		t_coord axis, double half_height, t_coord *cap_normal)
{
	t_coord	cap_center;
	double	denom;
	double	t;
	t_coord	hit_point;
	int		i;

	i = 0;
	while (i < 2)
	{
		cap_center = add(cylinder.position,
			scale(axis, (i == 0 ? -1 : 1) * half_height));
		denom = dot(ray.direction, axis);
		if (fabs(denom) > 1e-6)
		{
			t = dot(subtract(cap_center, ray.origin), axis) / denom;
			if (t >= 0)
			{
				hit_point = add(ray.origin, scale(ray.direction, t));
				if (length(subtract(hit_point, cap_center))
					<= cylinder.diameter / 2)
				{
					*cap_normal = i == 0 ? scale(axis, -1) : axis;
					return (t);
				}
			}
		}
		i++;
	}
	return (-1);
}

static void	set_hit_record(t_hit_record *rec, t_ray ray, double t,
		t_coord normal, t_rgb color)
{
	*closest_dist() = t;
	*cylinder_dist() = t;
	rec->t = t;
	rec->p = add(ray.origin, scale(ray.direction, t));
	rec->normal = normal;
	rec->color = color;
	rec->hit = 1;
}

static t_coord	calculate_body_normal(t_ray ray, t_cylinder cylinder,
		t_coord axis, double t)
{
	t_coord	hit_point;
	t_coord	center_to_hit;
	t_coord	radial_vector;

	hit_point = add(ray.origin, scale(ray.direction, t));
	center_to_hit = subtract(hit_point, cylinder.position);
	radial_vector = subtract(center_to_hit, scale(axis, dot(center_to_hit, axis)));
	return (norm(radial_vector));
}

void	render_cylinder(t_ray ray, t_cylinder cylinder, t_hit_record *rec)
{
	t_coord		axis;
	t_coord		oc;
	t_double	coeff;
	t_double	t;
	t_coord		cap_normal;
	double		half_height;

	axis = norm(cylinder.vector_norm);
	oc = subtract(ray.origin, cylinder.position);
	calculate_cylinder_coefficients(ray, cylinder, axis, oc, &coeff);
	if (!solve_quadratic(&coeff, &t))
		return ;
	t.c = intersect_cylinder_body(ray, cylinder, axis, &t);
	half_height = cylinder.height / 2;
	t.disc = intersect_cylinder_cap(ray, cylinder, axis, half_height, &cap_normal);
	if (t.c < 0 && t.disc < 0 && t.c > *closest_dist() && t.disc > *closest_dist()
		&& t.c > *cylinder_dist() && t.disc > *cylinder_dist())
		return ;
	if ((t.c < t.disc || t.disc < 0) && t.c >= 0)
		set_hit_record(rec, ray, t.c,
			calculate_body_normal(ray, cylinder, axis, t.c), cylinder.color);
	else
		set_hit_record(rec, ray, t.disc, cap_normal, cylinder.color);
}
