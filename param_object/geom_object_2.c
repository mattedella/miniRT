/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geom_object_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:00:34 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/22 11:10:14 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	get_sphere_2(char **mat, char **file, t_minirt *data, int i)
{
	char	**tmp;

	tmp = ft_split(mat[3], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2] || check_num(tmp) == 1 || tmp[3] != NULL)
		(void)(printf("Error color sphere: insert more data\n")
			+ quit(4, data->win_data, mat, file));
	data->sphere[i].color.x = ft_atod(tmp[0]);
	data->sphere[i].color.y = ft_atod(tmp[1]);
	data->sphere[i].color.z = ft_atod(tmp[2]);
	free_mat(tmp);
	check_color_range(data->sphere[i].color, data->win_data, mat, file);
	data->sphere[i].flag = 1;
}

void	get_sphere(char **mat, char **file, t_minirt *data, int i)
{
	char	**tmp;

	if (check_num(mat) == 1 || check_arg(mat, 's') == 1)
		(void)(printf("Error: sphere data not valid\n")
			+ quit(3, data->win_data, mat, file));
	tmp = ft_split(mat[1], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2] || check_num(tmp) == 1 || tmp[3] != NULL)
		(void)(printf("Error position sphere: insert more data\n")
			+ quit(3, data->win_data, mat, file));
	data->sphere[i].position.x = ft_atod(tmp[0]);
	data->sphere[i].position.y = ft_atod(tmp[1]);
	data->sphere[i].position.z = ft_atod(tmp[2]);
	free_mat(tmp);
	if (check_comma(mat[2]) == 1)
		(void)(printf("Error sphere: diameter not valid\n")
			+ quit(3, data->win_data, mat, file));
	data->sphere[i].diameter = ft_atod(mat[2]);
	get_sphere_2(mat, file, data, i);
}
