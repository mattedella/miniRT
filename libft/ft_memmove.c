/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:31:55 by mdella-r          #+#    #+#             */
/*   Updated: 2023/10/18 13:50:43 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*t1;
	unsigned char	*t2;

	i = 0;
	t1 = (unsigned char *) dest;
	t2 = (unsigned char *) src;
	if (t1 == NULL && t2 == NULL)
		return (NULL);
	if (t2 < t1)
	{
		i = n + 1;
		while (--i > 0)
			t1[i - 1] = t2[i - 1];
	}
	else
	{
		i = -1;
		while (++i < n)
			t1[i] = t2[i];
	}
	return (t1);
}
