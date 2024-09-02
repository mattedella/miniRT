/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:22:46 by mdella-r          #+#    #+#             */
/*   Updated: 2023/10/17 19:14:23 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*t1;
	char		*t2;

	i = 0;
	t1 = (char *) dest;
	t2 = (char *) src;
	if (t1 == NULL && t2 == NULL)
		return (NULL);
	while (i < n)
	{
		t1[i] = t2[i];
		i++;
	}
	return (t1);
}
