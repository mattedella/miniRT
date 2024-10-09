/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initMiniRT.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:26:24 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/08 12:30:24 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

void	init_sphere(t_minirt *data, int n_cmd)
{
	int	i;

	i = 0;
	if (n_cmd > 0)
		data->sphere = my_calloc(sizeof(t_sphere), n_cmd);
	while (i < n_cmd && n_cmd != 0)
	{
		data->sphere[i].position.x = 0;
		data->sphere[i].position.y = 0;
		data->sphere[i].position.z = 0;
		data->sphere[i].diameter = 0;
		data->sphere[i].color.x = 0;
		data->sphere[i].color.y = 0;
		data->sphere[i].color.z = 0;
		data->sphere[i].flag = 0;
		i++;
	}
}

void	init_cylinder(t_minirt *data, int n_cmd)
{
	int	i;

	i = 0;
	if (n_cmd > 0)	
		data->cylinder = my_calloc(sizeof(t_cylinder),n_cmd);
	while (i < n_cmd && n_cmd != 0)
	{
		data->cylinder[i].position.x = 0;
		data->cylinder[i].position.y = 0;
		data->cylinder[i].position.z = 0;
		data->cylinder[i].diameter = 0;
		data->cylinder[i].height = 0;
		data->cylinder[i].vector_norm.x = 0;
		data->cylinder[i].vector_norm.y = 0;
		data->cylinder[i].vector_norm.z = 0; 
		data->cylinder[i].color.x = 0;
		data->cylinder[i].color.y = 0;
		data->cylinder[i].color.z = 0;
		data->cylinder[i].flag = 0;
		i++;
	}
}

void	init_plane(t_minirt *data, int n_cmd)
{
	int	i;

	i = 0;
	if (n_cmd > 0)
		data->plane = my_calloc(sizeof(t_plane), n_cmd);
	while (i < n_cmd && n_cmd != 0)
	{
		data->plane[i].position.x = 0;
		data->plane[i].position.y = 0;
		data->plane[i].position.z = 0;
		data->plane[i].vector_norm.x = 0;
		data->plane[i].vector_norm.y = 0;
		data->plane[i].vector_norm.z = 0; 
		data->plane[i].color.x = 0;
		data->plane[i].color.y = 0;
		data->plane[i].color.z = 0;
		data->plane[i].flag = 0;
		i++;
	}
}

void	init_data(t_minirt *data, t_wdata *win_data)
{
	data->alight = my_calloc(sizeof(t_alight), 1);
	data->camera = my_calloc(sizeof(t_camera), 1);
	data->light = my_calloc(sizeof(t_light), 1);
	data->win_data = win_data;
}

void	init_window(t_wdata *win_data)
{
	win_data->mlx = mlx_init();
	win_data->win = mlx_new_window(win_data->mlx, WIN_WIDTH, WIN_HEIGHT,
			"MiniRT");
	win_data->img = mlx_new_image(win_data->mlx, WIN_WIDTH, WIN_HEIGHT);
	win_data->addr = mlx_get_data_addr(win_data->img, &win_data->bits_per_pixel,
			&win_data->line_length, &win_data->endian);
	if (!win_data->win)
		write(2, "Error: window initialization failed\n", 36);
}
