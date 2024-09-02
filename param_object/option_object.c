/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:31:55 by mdella-r          #+#    #+#             */
/*   Updated: 2024/09/02 17:07:17 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

void	get_ambient_light(char **mat, t_minirt *data)
{
	char	**tmp;

	tmp = ft_split(mat[2], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		(void)(printf("Error: insert more data") + ft_exit(3));
	data->alight->ratio = ft_atod(mat[1]);
	check_ratio_light(data->alight->ratio);
	data->alight->color.x = ft_atoi(tmp[0]);
	data->alight->color.y = ft_atoi(tmp[1]);
	data->alight->color.z = ft_atoi(tmp[2]);
	free_mat(tmp);
	check_color_range((data->alight->color));
}

void	get_camera(char **mat, t_minirt *data)
{
	char	**tmp;

	tmp = ft_split(mat[1], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		(void)(printf("Error: insert more data") + ft_exit(3));
	data->camera->position.x = ft_atod(tmp[0]);
	data->camera->position.y = ft_atod(tmp[1]);
	data->camera->position.z = ft_atod(tmp[2]);
	free_mat(tmp);
	tmp = ft_split(mat[2], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		(void)(printf("Error: insert more data") + ft_exit(3));
	data->camera->vector_norm.x = ft_atod(tmp[0]);
	data->camera->vector_norm.y = ft_atod(tmp[1]);
	data->camera->vector_norm.z = ft_atod(tmp[2]);
	free_mat(tmp);
	check_vector_range(data->camera->vector_norm);
	data->camera->fov = (atoi(mat [3]) * PI) / 180;
	check_fov(data->camera->fov);
}

void	get_light(char **mat, t_minirt *data)
{
	char	**tmp;

	tmp = ft_split(mat[1], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		(void)(printf("Error: insert more data") + ft_exit(3));
	data->light->position.x = ft_atod(tmp[0]);
	data->light->position.y = ft_atod(tmp[1]);
	data->light->position.z = ft_atod(tmp[2]);
	free_mat(tmp);
	data->light->brightness = ft_atod(mat[2]);
	check_ratio_light(data->light->brightness);
	tmp = ft_split(mat[3], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		(void)(printf("Error: insert more data") + ft_exit(3));
	data->light->color.x = ft_atoi(tmp[0]);
	data->light->color.y = ft_atoi(tmp[1]);
	data->light->color.z = ft_atoi(tmp[2]);
	free_mat(tmp);
	check_color_range(data->light->color);
}
