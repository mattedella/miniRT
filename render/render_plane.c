/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:03:02 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/15 15:54:02 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	render_plane(t_ray ray, t_plane plane, t_wdata *win_data, t_coord pixel)
{
	double	t;
	double	numerator;
	double	denominator;

	denominator = dot(ray.direction, plane.vector_norm);
	if (denominator == 0)
		return ;
	numerator = dot(subtract(plane.position, ray.origin), plane.vector_norm);
	t = numerator / denominator;
	if (t > 0 && t < *closest_dist() && t < *plane_dist())
	{
		*closest_dist() = t;
		*plane_dist() = t;
		put_pixel(win_data, pixel.x, pixel.y, plane.color);
	}
}
