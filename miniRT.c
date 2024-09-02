/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:07:32 by mdella-r          #+#    #+#             */
/*   Updated: 2024/09/02 17:46:44 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

static t_minirt	*set_malloc(void)
{
	t_minirt	*data;
	t_wdata		win_data;
	
	data = my_calloc(sizeof(t_minirt));
	init_window(&win_data);
	init_data(data, &win_data);
	return (data);
}

void	check_object(t_minirt *data, char **file)
{
	t_index id;

	id.i = 0;
	id.j = 0;
	id.k = 0;
	id.t = 0;
	while (file[id.i])
	{
		printf("%c\n", file[id.i][0]);
		if (ft_strncmp(file[id.i], "sp ", 3) == 0)
			id.j++;
		else if (ft_strncmp(file[id.i], "pl", 3) == 0)
			id.k++;
		else if (ft_strncmp(file[id.i], "cy", 3) == 0)
			id.t++;
		id.i++;
	}
	init_plane(data, id.k);
	init_sphere(data, id.j);
	init_cylinder(data, id.t);
}

static void	get_object(char **file, t_minirt *data, t_index *id)
{
	if (ft_strncmp(file[0], "sp", 3) == 0)
	{
		get_sphere(file, data, id->j);
		id->j++;
	}
	if (ft_strncmp(file[0], "pl", 3) == 0)
	{
		get_plane(file, data, id->k);
		id->k++;
	}
	if (ft_strncmp(file[0], "cy", 3) == 0)
	{
		get_cylinder(file, data, id->t);
		id ->t++;
	}
}

static void	get_param(char **file, t_minirt *data)
{
	char	**tmp;
	t_index	id;

	id.i = 0;
	id.j = 0;
	id.k = 0;
	id.t = 0;
	tmp = NULL;
	while(file[id.i])
	{
		tmp = ft_split(file[id.i], ' ');
		if (tmp[0][0] == 'A')
			get_ambient_light(tmp, data);
		else if (tmp[0][0] == 'C')
			get_camera(tmp, data);
		else if (tmp[0][0] == 'L')
			get_light(tmp, data);
		else if (ft_strncmp(tmp[0], "sp", 3) == 0
				|| ft_strncmp(tmp[0], "pl", 3) == 0
					|| ft_strncmp(tmp[0], "cy", 3) == 0)
			get_object(tmp, data, &id);
		else
			(void)(printf("Error: invalid argument") + ft_exit(1));
		free_mat(tmp);
		id.i++;
	}
	data->nbr_object = id.j + id.k + id.t;
}

static int	get_file(t_minirt *data, int len, char *arg)
{
	int		i;
	int 	fd;
	char	**file;

	i = -1;
	file = malloc(sizeof(char *) * (len + 1));
	fd = open(arg, O_RDONLY);
	if (fd < 0)
		return (printf("Error: corrupted file\n"), 1);
	if (open(arg, __O_DIRECTORY) > 0)
		return(printf("Error: %s is a directory\n", arg), 1);
	while (++i < len)
		file[i] = get_next_line(fd);
	file[i] = NULL;
	close(fd);
	check_object(data, file);
	get_param(file, data);
	free_mat(file);
	return (0);
}

static int	check_filename(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] == '.')
			break ;
		i++;
	}
	if (i == (int)ft_strlen(argv))
		return (1);
	if (ft_strncmp(argv + i, ".rt", 4) == 0)
		return (0);
	return (1);
}

int main(int argc, char **argv)
{
	int			fd;
	int			len;
	t_minirt	*data;

	if (argc != 2)
		return (printf("Error: number of argument is not correct\n"), 1);
	if (check_filename(argv[1]) == 0)
	{
		data = set_malloc();
		len = mat_get_len(argv[1]);
		fd = get_file(data, len, argv[1]);
		if (fd == 1)
			return (1);
		render(data);
		mlx_hook(data->win_data->win, 2, 1, &key_hook, data->win_data);
		mlx_hook(data->win_data->win, 17, 1L << 17, &press_x, data->win_data);
		mlx_loop(data->win_data->mlx);
	}
	else
		return (printf("Error: file is not correct\n"), 1);
	garbage_collector_free();
	return (0);
}
