/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:46:34 by mdella-r          #+#    #+#             */
/*   Updated: 2023/10/31 11:13:51 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	t;

	i = ft_strlen(dst);
	j = ft_strlen(src);
	t = 0;
	k = i;
	if (size == 0)
		return (j);
	while (src[t] != '\0' && k + t < (size - 1))
	{
		dst[k + t] = src[t];
		t++;
	}
	dst[t + k] = '\0';
	if (size < i)
		return (size + j);
	else
		return (i + j);
}
