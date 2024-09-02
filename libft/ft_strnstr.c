/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:05:19 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/28 16:14:45 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*b;
	char	*l;

	i = 0;
	j = 0;
	k = ft_strlen(little);
	b = (char *) big;
	l = (char *) little;
	if (l[0] == '\0')
		return (b);
	while (i < len && b[i] != '\0')
	{
		while (b[i + j] == l[j] && j + i < len)
		{
			if (j >= k - 1)
				return (&b[i]);
			j++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}
