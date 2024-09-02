/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:43:51 by mdella-r          #+#    #+#             */
/*   Updated: 2023/10/18 12:58:22 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t			i;
	unsigned char	*t;
	unsigned char	*s;

	i = 0;
	t = (unsigned char *) str1;
	s = (unsigned char *) str2;
	if (n <= 0)
		return (0);
	while (i < n && t[i] == s[i])
		i++;
	if (n == i)
		i--;
	return (t[i] - s[i]);
}
