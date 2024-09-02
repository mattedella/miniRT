/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 10:10:04 by mdella-r          #+#    #+#             */
/*   Updated: 2023/10/20 11:16:39 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*st;
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	t;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	k = -1;
	st = malloc(sizeof(char) * (i + j + 1));
	if (st == NULL)
		return (NULL);
	while (s1[++k] != '\0')
		st[k] = s1[k];
	t = k;
	k = -1;
	while (s2[++k] != '\0')
		st[t + k] = s2[k];
	st[t + k] = '\0';
	return (st);
}
