/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsRT.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:55:56 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/09 10:53:58 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

double	ft_atod(char *argv)
{
	double			r;
	double			n;
	unsigned short	i;
	unsigned short	j;

	r = 0;
	n = 0;
	i = 0;
	if (argv[i] == '-')
		i++;
	while (argv[i] && argv[i] != '.' && argv[i] != '\n')
		r = r * 10 + (argv[i++] - 48);
	j = i + 1;
	if (argv[i] == '.')
		while (argv[++i] && argv[i] != '\n')
			n = n * 10 + (argv[i] - 48);
	if (n != 0)
		r += n / pow(10, ft_strlen(argv + j));
	if (argv[0] == '-')
		return (r * -1);
	return (r);
}

void	free_mat(char **mat)
{
	int i;

	i = 0;
	while (mat[i])
		free(mat[i++]);
	free(mat);
	mat = NULL;
	return ;
}

size_t	mat_get_len(char *argv)
{
	char	*tmp;
	size_t	i;
	int		fd;

	i = 0;
	fd = open(argv, O_RDONLY);
	tmp = get_next_line(fd);
	while (tmp != NULL)
	{
		free(tmp);
		tmp = get_next_line(fd);
		i++;
	}
	free(tmp);
	close(fd);
	return(i);
}

int	mat_len(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
		i++;
	return (i);
}

int	ft_exit(int id)
{
	garbage_collector_free();
	exit(id);
}
