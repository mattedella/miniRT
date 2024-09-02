/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:44:41 by mdella-r          #+#    #+#             */
/*   Updated: 2023/10/18 16:46:39 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ciset(const char s1, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*st;

	i = 0;
	j = 0;
	k = ft_strlen(s1) - 1;
	while (s1[i] != '\0' && ciset(s1[i], set))
		i++;
	while (k > i && ciset(s1[k], set))
		k--;
	st = (char *)malloc(k - i + 2);
	if (st == 0)
		return (0);
	while (i < (k + 1))
	{
		st[j] = s1[i];
		i++;
		j++;
	}
	st[j] = '\0';
	return (st);
}
