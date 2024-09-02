/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geom_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:29:05 by mdella-r          #+#    #+#             */
/*   Updated: 2024/09/02 17:30:30 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

void	get_sphere(char **mat, t_minirt *data, int i)
{
	char	**tmp;

	printf("%d\n", i);
	tmp = ft_split(mat[1], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		(void)(printf("Error: insert more data") + ft_exit(3));
	data->sphere[i].position.x = ft_atod(tmp[0]);
	data->sphere[i].position.y = ft_atod(tmp[1]);
	data->sphere[i].position.z = ft_atod(tmp[2]);
	free_mat(tmp);
	data->sphere[i].diameter = ft_atod(mat[2]);
	tmp = ft_split(mat[3], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		(void)(printf("Error: insert more data") + ft_exit(4));
	data->sphere[i].color.x = ft_atod(tmp[0]);
	data->sphere[i].color.y = ft_atod(tmp[1]);
	data->sphere[i].color.z = ft_atod(tmp[2]);
	free_mat(tmp);
	check_color_range(data->sphere[i].color);
	data->sphere[i].flag = 1;
}

void	get_plane(char **mat, t_minirt *data, int i)
{
	char	**tmp;

	tmp = ft_split(mat[1], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		(void)(printf("Error: insert more data") + ft_exit(3));
	data->plane[i].position.x = ft_atod(tmp[0]);
	data->plane[i].position.y = ft_atod(tmp[1]);
	data->plane[i].position.z = ft_atod(tmp[2]);
	free_mat(tmp);
	tmp = ft_split(mat[2], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		(void)(printf("Error: insert more data") + ft_exit(3));
	data->plane[i].vector_norm.x = ft_atod(tmp[0]);
	data->plane[i].vector_norm.y = ft_atod(tmp[1]);
	data->plane[i].vector_norm.z = ft_atod(tmp[2]);
	check_vector_range(data->plane[i].vector_norm);
	free_mat(tmp);
	tmp = ft_split(mat[3], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		(void)(printf("Error: insert more data") + ft_exit(3));
	data->plane[i].color.x = ft_atod(tmp[0]);
	data->plane[i].color.y = ft_atod(tmp[1]);
	data->plane[i].color.z = ft_atod(tmp[2]);
	free_mat(tmp);
	check_color_range(data->plane[i].color);
	data->plane[i].flag = 1;
}

void	get_cylinder(char **mat, t_minirt *data, int i)
{
	char	**tmp;

	tmp = ft_split(mat[1], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		(void)(printf("Error: insert more data") + ft_exit(3));
	data->cylinder[i].position.x = ft_atod(tmp[0]);
	data->cylinder[i].position.y = ft_atod(tmp[1]);
	data->cylinder[i].position.z = ft_atod(tmp[2]);
	free_mat(tmp);
	tmp = ft_split(mat[2], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		(void)(printf("Error: insert more data") + ft_exit(3));
	data->cylinder[i].vector_norm.x = ft_atod(tmp[0]);
	data->cylinder[i].vector_norm.y = ft_atod(tmp[1]);
	data->cylinder[i].vector_norm.z = ft_atod(tmp[2]);
	free_mat(tmp);
	check_vector_range(data->cylinder[i].vector_norm);
	data->cylinder[i].diameter = ft_atod(mat[3]);
	data->cylinder[i].height = ft_atod(mat[4]);
	tmp = ft_split(mat[5], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		(void)(printf("Error: insert more data") + ft_exit(3));
	data->cylinder[i].color.x = ft_atod(tmp[0]);
	data->cylinder[i].color.y = ft_atod(tmp[1]);
	data->cylinder[i].color.z = ft_atod(tmp[2]);
	free_mat(tmp);
	check_color_range(data->cylinder[i].color);
	data->cylinder[i].flag = 1;
}
