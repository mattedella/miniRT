/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:00:24 by mdella-r          #+#    #+#             */
/*   Updated: 2023/10/20 10:44:15 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*st;
	size_t	i;

	i = -1;
	if (start > ft_strlen(s))
	{
		st = malloc(sizeof(char) * 1);
		if (st == NULL)
			return (NULL);
		*st = '\0';
		return (st);
	}
	s = s + start;
	if (ft_strlen(s) <= len)
		st = malloc(sizeof(char) * (ft_strlen(s) + 1));
	else
		st = malloc(sizeof(char) * (len + 1));
	if (st == NULL)
		return (NULL);
	while (s[++i] != '\0' && i < len)
		st[i] = s[i];
	st[i] = '\0';
	return (st);
}
