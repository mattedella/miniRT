/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:54:19 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/22 10:44:43 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_file(char **file)
{
	int	i;
	int	j;

	i = -1;
	while (file[++i])
	{
		j = -1;
		while (file[i][++j])
		{
			if (ft_isalnum(file[i][j]) == 0 && file[i][j] != ','
				&& file[i][j] != '.' && file[i][j] != ' '
				&& file[i][j] != '\n' && file[i][j] != '-')
				return (1);
		}
	}
	return (0);
}

int	check_num(char **file)
{
	int	i;
	int	j;

	i = 0;
	while (file[++i])
	{
		j = -1;
		while (file[i][++j])
		{
			if (ft_isalpha(file[i][j]) == 1 && file[i][j] != ','
				&& file[i][j] != '.' && file[i][j] != ' '
				&& file[i][j] != '\n' && file[i][j] != '-')
				return (1);
		}
	}
	return (0);
}

static int	check_arg_3(char **file, char c)
{
	int	i;

	i = 0;
	if (c == 'p')
	{
		while (file[i])
			i++;
		if (i != 4)
			return (1);
	}
	return (0);
}

static int	check_arg_2(char **file, char c)
{
	int	i;

	i = 0;
	if (c == 'C')
	{
		while (file[i])
			i++;
		if (i != 4)
			return (1);
	}
	else if (c == 'A')
	{
		while (file[i])
			i++;
		if (i != 3)
			return (1);
	}
	else if (c == 'L')
	{
		while (file[i])
			i++;
		if (i != 4)
			return (1);
	}
	return (0);
}

int	check_arg(char **file, char c)
{
	int	i;

	i = 0;
	if (c == 'c')
	{
		while (file[i])
			i++;
		if (i != 6)
			return (1);
	}
	else if (c == 's')
	{
		while (file[i])
			i++;
		if (i != 4)
			return (1);
	}
	else if (check_arg_3(file, c) == 1)
		return (1);
	else if (check_arg_2(file, c) == 1)
		return (1);
	return (0);
}
