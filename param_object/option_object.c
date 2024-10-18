/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:31:55 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/18 15:33:22 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_ambient_light(char **mat, char **file, t_minirt *data)
{
	char	**tmp;

	tmp = ft_split(mat[2], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		(void)(printf("Error color ambient light: insert more data")
			+ quit(3, data->win_data, mat, file));
	data->alight->ratio = ft_atod(mat[1]);
	check_ratio_light(data->alight->ratio, data->win_data, mat, file);
	data->alight->color.x = ft_atoi(tmp[0]);
	data->alight->color.y = ft_atoi(tmp[1]);
	data->alight->color.z = ft_atoi(tmp[2]);
	free_mat(tmp);
	check_color_range(data->alight->color, data->win_data, mat, file);
}

void	get_camera(char **mat, char **file, t_minirt *data)
{
	char	**tmp;

	tmp = ft_split(mat[1], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		(void)(printf("Error position camera: insert more data")
			+ quit(3, data->win_data, mat, file));
	data->camera->position.x = ft_atod(tmp[0]);
	data->camera->position.y = ft_atod(tmp[1]);
	data->camera->position.z = ft_atod(tmp[2]);
	free_mat(tmp);
	tmp = ft_split(mat[2], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		(void)(printf("Error normal vector camera: insert more data")
			+ quit(3, data->win_data, mat, file));
	data->camera->vector_norm.x = ft_atod(tmp[0]);
	data->camera->vector_norm.y = ft_atod(tmp[1]);
	data->camera->vector_norm.z = ft_atod(tmp[2]);
	free_mat(tmp);
	check_vector_range(data->camera->vector_norm, data->win_data, mat, file);
	data->camera->fov = ft_atod(mat[3]);
	data->camera->fov = (ft_atod(mat[3]) * PI) / 180;
	check_fov(data->camera->fov, data->win_data, mat, file);
	if (data->camera->fov == PI)
		data->camera->fov = (179 * PI) / 180;
}

void	get_light(char **mat, char **file, t_minirt *data)
{
	char	**tmp;

	tmp = ft_split(mat[1], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		(void)(printf("Error position light: insert more data")
			+ quit(3, data->win_data, mat, file));
	data->light->position.x = ft_atod(tmp[0]);
	data->light->position.y = ft_atod(tmp[1]);
	data->light->position.z = ft_atod(tmp[2]);
	free_mat(tmp);
	data->light->brightness = ft_atod(mat[2]);
	check_ratio_light(data->light->brightness, data->win_data, mat, file);
	tmp = ft_split(mat[3], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		(void)(printf("Error color light: insert more data")
			+ quit(3, data->win_data, mat, file));
	data->light->color.x = ft_atoi(tmp[0]);
	data->light->color.y = ft_atoi(tmp[1]);
	data->light->color.z = ft_atoi(tmp[2]);
	free_mat(tmp);
	check_color_range(data->light->color, data->win_data, mat, file);
}
