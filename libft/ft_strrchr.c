/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:05:37 by mdella-r          #+#    #+#             */
/*   Updated: 2023/10/30 20:56:28 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*t;

	i = ft_strlen(s);
	t = (char *) s;
	while (i >= 0)
	{
		if ((unsigned char)c == (unsigned char)t[i])
		{
			return (t + i);
		}
		i--;
	}
	return (0);
}
