/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:04:48 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/18 16:34:25 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_double	calculate_cylinder_coefficient(t_ray ray, t_cylinder cylinder,
				t_coord	axis)
{
	t_double	coeffs;
	t_coord		oc;

	oc = subtract(ray.origin, cylinder.position);
	coeffs.a = dot(ray.direction, ray.direction)
		- pow(dot(ray.direction, axis), 2);
	coeffs.b = 2 * (dot(ray.direction, oc)
			- dot(ray.direction, axis) * dot(oc, axis));
	coeffs.c = dot(oc, oc) - pow(dot(oc, axis), 2)
		- pow(cylinder.diameter / 2, 2);
	return (coeffs);
}

static int	solve_quadratics(t_double coeffs, t_double *t)
{
	double	discriminant;
	double	sqrt_discriminant;
	double	temp;

	discriminant = coeffs.b * coeffs.b - 4 * coeffs.a * coeffs.c;
	if (discriminant < 0)
		return (0);
	sqrt_discriminant = sqrt(discriminant);
	t->c = (-coeffs.b - sqrt_discriminant) / (2 * coeffs.a);
	t->disc = (-coeffs.b + sqrt_discriminant) / (2 * coeffs.a);
	if (t->c > t->disc)
	{
		temp = t->c;
		t->c = t->disc;
		t->disc = temp;
	}
	return (1);
}

static double	intersect_cylinder_bodys(t_ray ray, t_cylinder cylinder,
		t_coord axis, t_double *t)
{
	t_coord	hit_point;
	t_coord	center_to_hit;
	double	half_height;

	half_height = cylinder.height / 2;
	if (t->c >= 0)
	{
		hit_point = add(ray.origin, scale(ray.direction, t->c));
		center_to_hit = subtract(hit_point, cylinder.position);
		if (fabs(dot(center_to_hit, axis)) <= half_height)
			return (t->c);
	}
	if (t->disc >= 0)
	{
		hit_point = add(ray.origin, scale(ray.direction, t->disc));
		center_to_hit = subtract(hit_point, cylinder.position);
		if (fabs(dot(center_to_hit, axis)) <= half_height)
			return (t->disc);
	}
	return (-1);
}

static t_hit_record	set_hit_records(t_ray ray, double t,
		t_coord normal, t_rgb color)
{
	t_hit_record	rec;

	rec.t = t;
	rec.p = add(ray.origin, scale(ray.direction, t));
	rec.normal = normal;
	rec.color = color;
	rec.hit = 1;
	rec.object_type = CYLINDER;
	return (rec);
}

void	render_cylinder(t_ray ray, t_cylinder cylinder, t_hit_record *rec)
{
	t_double	coef;
	t_double	t;
	t_coord		cap_normal;
	t_coord		axis;

	axis = norm(cylinder.vector_norm);
	coef = calculate_cylinder_coefficient(ray, cylinder, axis);
	if (!solve_quadratics(coef, &t))
		return ;
	t.a = intersect_cylinder_bodys(ray, cylinder, axis, &t);
	t.b = intersect_cylinder_cap(ray, cylinder, axis, &cap_normal);
	if (t.a < 0 && t.b < 0)
		return ;
	if ((t.a < t.b || t.b < 0) && t.a >= 0 && t.a < *cylinder_dist())
	{
		*rec = set_hit_records(ray, t.a,
				calculate_body_normal(ray, cylinder, axis, t.a),
				cylinder.color);
		set_dist(t.a);
	}
	else if (t.b >= 0 && t.b < *cylinder_dist())
	{
		*rec = set_hit_records(ray, t.b, cap_normal, cylinder.color);
		set_dist(t.b);
	}
}
