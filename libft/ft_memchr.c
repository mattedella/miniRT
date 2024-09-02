/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:20:56 by mdella-r          #+#    #+#             */
/*   Updated: 2023/10/18 12:50:14 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*t;
	unsigned int	i;

	i = 0;
	t = (unsigned char *)str;
	while (i < n)
	{
		if ((unsigned char)c == t[i])
			return (t + i);
		i++;
	}
	return (0);
}
