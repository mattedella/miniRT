/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:32:05 by mdella-r          #+#    #+#             */
/*   Updated: 2023/10/17 17:57:57 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*st;
	unsigned int	i;

	i = 0;
	st = malloc(ft_strlen(s) + 1);
	if (st == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		st[i] = f(i, s[i]);
		i++;
	}
	st[i] = '\0';
	return (st);
}
