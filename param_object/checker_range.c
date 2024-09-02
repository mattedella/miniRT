/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_range.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaye <kfaye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:07:59 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/30 15:47:47 by kfaye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

void	check_color_range(t_rgb color)
{
	if (color.x >= 256 || color.x <= -1)
		(void)(printf("Error: color red out of range\n") + ft_exit(2));
	if (color.y >= 256 || color.y <= -1)
		(void)(printf("Error: color green out of range\n") + ft_exit(3));
	if (color.z >= 256 || color.z <= -1)
		(void)(printf("Error: color blue out of range\n") + ft_exit(4));
	return ;
}

void	check_vector_range(t_coord pos)
{
	if (pos.x > 1 || pos.x < -1)
		(void)(printf("Error: vector x out of range\n") + ft_exit(5));
	if (pos.y > 1 || pos.y < -1)
		(void)(printf("Error: vector y out of range\n") + ft_exit(6));
	if (pos.z > 1 || pos.z < -1)
		(void)(printf("Error: vector z out of range\n") + ft_exit(7));
	return ;
}

void	check_ratio_light(double light)
{
	if (light < 0 || light > 1)
		(void)(printf("Error: ratio light out of range\n") + ft_exit(8));
	return ;
}

void	check_fov(int fov)
{
	if (fov < 0 || fov > 180)
		(void)(printf("Error: fov out of range\n") + ft_exit(9));
	return ;
}
