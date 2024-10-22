/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geom_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:29:05 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/22 11:09:18 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	get_plane_2(char **mat, char **file, t_minirt *data, int i)
{
	char	**tmp;

	tmp = ft_split(mat[3], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2] || check_num(tmp) == 1 || tmp[3] != NULL)
		(void)(printf("Error color plane: insert more data\n")
			+ quit(3, data->win_data, mat, file));
	data->plane[i].color.x = ft_atod(tmp[0]);
	data->plane[i].color.y = ft_atod(tmp[1]);
	data->plane[i].color.z = ft_atod(tmp[2]);
	free_mat(tmp);
	check_color_range(data->plane[i].color, data->win_data, mat, file);
	data->plane[i].flag = 1;
}

void	get_plane(char **mat, char **file, t_minirt *data, int i)
{
	char	**tmp;

	if (check_num(mat) == 1 || check_arg(mat, 'p') == 1)
		(void)(printf("Error: plane data not valid\n")
			+ quit(3, data->win_data, mat, file));
	tmp = ft_split(mat[1], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2] || check_num(tmp) == 1 || tmp[3] != NULL)
		(void)(printf("Error position plane: insert more data\n")
			+ quit(3, data->win_data, mat, file));
	data->plane[i].position.x = ft_atod(tmp[0]);
	data->plane[i].position.y = ft_atod(tmp[1]);
	data->plane[i].position.z = ft_atod(tmp[2]);
	free_mat(tmp);
	tmp = ft_split(mat[2], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2] || check_num(tmp) == 1 || tmp[3] != NULL)
		(void)(printf("Error normal vector plane: insert more data\n")
			+ quit(3, data->win_data, mat, file));
	data->plane[i].vector_norm.x = ft_atod(tmp[0]);
	data->plane[i].vector_norm.y = ft_atod(tmp[1]);
	data->plane[i].vector_norm.z = ft_atod(tmp[2]);
	check_vector_range(data->plane[i].vector_norm, data->win_data, mat, file);
	free_mat(tmp);
	get_plane_2(mat, file, data, i);
}

static void	get_cylinder_2(char **mat, char **file, t_minirt *d, int i)
{
	char	**tmp;

	if (d->cylinder[i].vector_norm.x == 0 && d->cylinder[i].vector_norm.y == 0
		&& d->cylinder[i].vector_norm.z == -1)
		d->cylinder[i].vector_norm.z = 1;
	if (check_comma(mat[3]) == 1 || check_comma(mat[4]) == 1)
		(void)(printf("Error cylinder: diameter or height not valid\n")
			+ quit(3, d->win_data, mat, file));
	d->cylinder[i].diameter = ft_atod(mat[3]);
	d->cylinder[i].height = ft_atod(mat[4]);
	tmp = ft_split(mat[5], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2] || check_num(tmp) == 1 || tmp[3] != NULL)
		(void)(printf("Error color cylinder: insert more data\n")
			+ quit(3, d->win_data, mat, file));
	d->cylinder[i].color.x = ft_atod(tmp[0]);
	d->cylinder[i].color.y = ft_atod(tmp[1]);
	d->cylinder[i].color.z = ft_atod(tmp[2]);
	free_mat(tmp);
	check_color_range(d->cylinder[i].color, d->win_data, mat, file);
	d->cylinder[i].flag = 1;
}

void	get_cylinder(char **mat, char **file, t_minirt *d, int i)
{
	char	**tmp;

	if (check_num(mat) == 1 || check_arg(mat, 'c') == 1)
		(void)(printf("Error: cylinder data not valid\n")
			+ quit(3, d->win_data, mat, file));
	tmp = ft_split(mat[1], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2] || check_num(tmp) == 1 || tmp[3] != NULL)
		(void)(printf("Error position cylinder: insert more data\n")
			+ quit(3, d->win_data, mat, file));
	d->cylinder[i].position.x = ft_atod(tmp[0]);
	d->cylinder[i].position.y = ft_atod(tmp[1]);
	d->cylinder[i].position.z = ft_atod(tmp[2]);
	free_mat(tmp);
	check_vector_range(d->cylinder[i].vector_norm,
		d->win_data, mat, file);
	tmp = ft_split(mat[2], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2] || check_num(tmp) == 1 || tmp[3] != NULL)
		(void)(printf("Error normal vector cylinder: insert more data\n")
			+ quit(3, d->win_data, mat, file));
	d->cylinder[i].vector_norm.x = ft_atod(tmp[0]);
	d->cylinder[i].vector_norm.y = ft_atod(tmp[1]);
	d->cylinder[i].vector_norm.z = ft_atod(tmp[2]);
	free(tmp);
	get_cylinder_2(mat, file, d, i);
}
