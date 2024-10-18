/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_light_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:04:21 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/18 16:11:50 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	set_hit(int *hit, double *closest,
			t_hit_record *rec, t_hit_record temp_rec)
{
	*hit = 1;
	*closest = temp_rec.t;
	*rec = temp_rec;
}

int	intersect_scene(t_minirt *data, t_ray ray, t_hit_record *rec)
{
	int				hit_anything;
	double			closest_so_far;
	t_hit_record	temp_rec;
	int				i;

	hit_anything = 0;
	closest_so_far = INFINITY;
	i = -1;
	init_hit_record(&temp_rec);
	while (++i < data->nbr_sphere)
		if (intersect_sphere(ray, data->sphere[i], &temp_rec)
			&& temp_rec.t < closest_so_far)
			set_hit(&hit_anything, &closest_so_far, rec, temp_rec);
	i = -1;
	while (++i < data->nbr_plane)
		if (intersect_plane(ray, data->plane[i], &temp_rec)
			&& temp_rec.t < closest_so_far)
			set_hit(&hit_anything, &closest_so_far, rec, temp_rec);
	i = -1;
	while (++i < data->nbr_cylinder)
		if (intersect_cylinder(ray, data->cylinder[i], &temp_rec)
			&& temp_rec.t < closest_so_far)
			set_hit(&hit_anything, &closest_so_far, rec, temp_rec);
	return (hit_anything);
}
