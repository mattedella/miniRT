/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:10:24 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/11 11:49:44 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_object(t_minirt *data, char **file)
{
	t_index	id;

	id.i = 0;
	id.j = 0;
	id.k = 0;
	id.t = 0;
	while (file[id.i])
	{
		if (ft_strncmp(file[id.i], "sp ", 3) == 0)
			id.j++;
		else if (ft_strncmp(file[id.i], "pl ", 3) == 0)
			id.k++;
		else if (ft_strncmp(file[id.i], "cy ", 3) == 0)
			id.t++;
		id.i++;
	}
	if (id.j == 0 && id.k == 0 && id.t == 0)
		(void)(printf("Error: no object to render\n")
			+ quit(104, data->win_data, file, NULL));
	init_plane(data, id.k);
	init_sphere(data, id.j);
	init_cylinder(data, id.t);
}

static int	check_camera(t_minirt *data, char **file, int i)
{
	(void)data;
	if (ft_strncmp(file[i], "C ", 2) == 0)
		return (1);
	else
		return (0);
}

static int	check_ambient_light(t_minirt *data, char **file, int i)
{
	(void)data;
	if (ft_strncmp(file[i], "A ", 2) == 0)
		return (1);
	else
		return (0);
}

static int	check_light(t_minirt *data, char **file, int i)
{
	(void)data;
	if (ft_strncmp(file[i], "L ", 2) == 0)
		return (1);
	else
		return (0);
}

void	check_option(t_minirt *data, char **file)
{
	t_index	id;

	id.i = 0;
	id.j = 0;
	id.k = 0;
	id.t = 0;
	while (file[id.i])
	{
		id.j += check_camera(data, file, id.i);
		if (id.j > 1)
			(void)(printf("Error : too much camera\n")
				+ quit(100, data->win_data, file, NULL));
		id.k += check_ambient_light(data, file, id.i);
		if (id.k > 1)
			(void)(printf("Error : too much ambient light\n")
				+ quit(100, data->win_data, file, NULL));
		id.t += check_light(data, file, id.i);
		if (id.t > 1)
			(void)(printf("Error : too much light\n")
				+ quit(100, data->win_data, file, NULL));
		id.i++;
	}
	if (id.j == 0 || id.k == 0 || id.t == 0)
		(void)(printf("Error: missing obtion\n")
			+ quit(101, data->win_data, file, NULL));
}
