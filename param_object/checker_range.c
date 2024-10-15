/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_range.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:07:59 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/15 15:39:59 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_color_range(t_rgb color, t_wdata *data, char **mat, char **file)
{
	if (color.x >= 256 || color.x <= -1)
		(void)(printf("Error: color red out of range\n")
			+ quit(2, data, mat, file));
	if (color.y >= 256 || color.y <= -1)
		(void)(printf("Error: color green out of range\n")
			+ quit(3, data, mat, file));
	if (color.z >= 256 || color.z <= -1)
		(void)(printf("Error: color blue out of range\n")
			+ quit(4, data, mat, file));
	return ;
}

void	check_vector_range(t_coord pos, t_wdata *data, char **mat, char **file)
{
	if (pos.x > 1 || pos.x < -1)
		(void)(printf("Error: vector x out of range\n")
			+ quit(5, data, mat, file));
	if (pos.y > 1 || pos.y < -1)
		(void)(printf("Error: vector y out of range\n")
			+ quit(6, data, mat, file));
	if (pos.z > 1 || pos.z < -1)
		(void)(printf("Error: vector z out of range\n")
			+ quit(7, data, mat, file));
	return ;
}

void	check_ratio_light(double light, t_wdata *data, char **mat, char **file)
{
	if (light < 0 || light > 1)
		(void)(printf("Error: ratio light out of range\n")
			+ quit(8, data, mat, file));
	return ;
}

void	check_fov(double fov, t_wdata *data, char **mat, char **file)
{
	if (fov < 0 || fov > PI)
		(void)(printf("Error: fov out of range\n") + quit(9, data, mat, file));
	return ;
}
