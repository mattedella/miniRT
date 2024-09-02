/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:08:22 by mdella-r          #+#    #+#             */
/*   Updated: 2023/10/17 12:42:01 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	s;
	int	n;

	i = 0;
	s = 0;
	n = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	while (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i - 1] == '+' || nptr[i - 1] == '-')
			return (0);
		if (nptr[i] == '-')
			s++;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = (n * 10 + nptr[i] - 48);
		i++;
	}
	if (s == 1)
		n = -n;
	return (n);
}
