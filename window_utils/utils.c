/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:03:27 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/09 15:01:08 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

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

int	key_hook(int keycode, t_wdata *w_data, t_minirt *data)
{
	(void)data;
	if (keycode == ESC_KEY)
		quit(0, w_data, NULL, NULL);
	return (0);
}
