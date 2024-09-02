/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:56:07 by mdella-r          #+#    #+#             */
/*   Updated: 2023/10/18 15:59:09 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(src);
	j = 0;
	if (size == 0)
		return (i);
	while (src[j] != '\0' && j < size - 1)
	{
		dst[j] = src[j];
		j++;
	}
	if (dst[j] != 0)
		dst[j] = '\0';
	return (i);
}
