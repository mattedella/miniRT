/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:03:27 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/18 15:36:36 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	quit(char id, t_wdata *data, char **mat, char **file)
{
	if (mat)
		free_mat(mat);
	if (file)
		free_mat(file);
	if (data)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	garbage_collector_free();
	exit(id);
}

int	press_x(t_wdata *data)
{
	quit(0, data, NULL, NULL);
	return (0);
}

void	put_pixel(t_wdata *win_data, int x, int y, t_rgb color)
{
	char	*dst;

	dst = win_data->addr + (y * win_data->line_length + x
			* (win_data->bits_per_pixel / 8));
	*(unsigned int *)dst = create_rgb(color.x, color.y, color.z);
}
