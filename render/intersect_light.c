/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:59:31 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/18 16:32:03 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	intersect_plane(t_ray ray, t_plane plane, t_hit_record *rec)
{
	double	numerator;
	double	denominator;
	double	t;

	numerator = dot(subtract(plane.position, ray.origin), plane.vector_norm);
	denominator = dot(ray.direction, plane.vector_norm);
	if (fabs(denominator) < 1e-6)
		return (0);
	t = numerator / denominator;
	if (t < 1e-6 || t >= rec->t)
		return (0);
	rec->t = t;
	rec->p = add(ray.origin, scale(ray.direction, t));
	rec->normal = plane.vector_norm;
	if (dot(ray.direction, rec->normal) > 0)
		rec->normal = scale(rec->normal, -1);
	rec->color = plane.color;
	rec->object_type = PLANE;
	rec->object = (void *)&plane;
	return (1);
}

int	intersect_cylinder(t_ray ray, t_cylinder cyl, t_hit_record *rec)
{
	t_coord		axis;
	t_coord		oc;
	t_double	coeff;
	t_double	t;
	t_coord		cap_normal;

	axis = norm(cyl.vector_norm);
	oc = subtract(ray.origin, cyl.position);
	coeff = calculate_cylinder_coefficients(ray, cyl, axis, oc);
	if (!solve_quadratic(&coeff, &t))
		return (0);
	t.c = intersect_cylinder_body(ray, cyl, axis, &t);
	t.disc = intersect_cylinder_cap(ray, cyl, axis, &cap_normal);
	if (t.c < 0 && t.disc < 0)
		return (0);
	if ((t.c < t.disc || t.disc < 0) && t.c >= 0)
		*rec = set_hit_record(ray, t.c,
				calculate_body_normal(ray, cyl, axis, t.c), cyl.color);
	else if (t.disc >= 0)
		*rec = set_hit_record(ray, t.disc, cap_normal, cyl.color);
	rec->hit = 1;
	return (1);
}

double	intersect_cylinder_cap(t_ray ray, t_cylinder c,
		t_coord axis, t_coord *cap_normal)
{
	t_coord		cap_center;
	t_coord		hit_point;
	t_double	id;
	int			i;

	i = -1;
	while (++i < 2)
	{
		cap_center = get_cap_center(i, c, axis);
		id.disc = dot(ray.direction, axis);
		if (fabs(id.disc) > 1e-6)
		{
			id.a = dot(subtract(cap_center, ray.origin), axis) / id.disc;
			if (id.a >= 0)
			{
				hit_point = add(ray.origin, scale(ray.direction, id.a));
				if (length(subtract(hit_point, cap_center)) <= c.diameter / 2)
				{
					get_cap_norm(i, cap_normal, axis);
					return (id.a);
				}
			}
		}
	}
	return (-1);
}
