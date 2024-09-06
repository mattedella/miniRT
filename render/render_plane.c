/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:03:02 by mdella-r          #+#    #+#             */
/*   Updated: 2024/09/06 10:22:52 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

void	render_plane(t_ray ray, t_plane plane, t_wdata *win_data, t_coord pixel)
{
	double	t;
	double	numerator;
	double	denominator;
	// t_rgb	color;
	
	// color = (t_rgb){0, 0, 0};
	numerator = vector_dot(vector_subtract(plane.position, ray.origin), plane.vector_norm);
	denominator = vector_dot(ray.direction, plane.vector_norm);
	t = numerator / denominator;
	if (t > 0)
		put_pixel(win_data, pixel.x, pixel.y, plane.color);
}
