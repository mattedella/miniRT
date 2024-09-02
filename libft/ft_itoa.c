/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:16:38 by mdella-r          #+#    #+#             */
/*   Updated: 2023/10/25 14:01:25 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

static long	intcount(long n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static long	getm(long n, int m)
{
	if (n / 10 == 0)
		return (m);
	else
		return (getm(n / 10, m * 10));
}

char	*ft_itoa(int n)
{
	size_t		i;
	size_t		m;
	long		nb;
	char		*st;

	i = 0;
	m = getm(n, 1);
	nb = (long) n;
	st = malloc((intcount(nb) + 1) * sizeof(char));
	if (st == NULL)
		return (0);
	if (nb < 0)
	{
		st[i] = '-';
		nb = -nb;
		i++;
	}
	while (m > 0)
	{
		st[i] = (nb / m) % 10 + 48;
		m = m / 10;
		i++;
	}
	st[i] = '\0';
	return (st);
}
