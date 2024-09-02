/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:46:01 by mdella-r          #+#    #+#             */
/*   Updated: 2023/10/18 14:25:19 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*d;
	int		i;
	char	*s1;

	s1 = (char *) s;
	i = 0;
	d = malloc (ft_strlen(s1) + 1);
	if (d == NULL)
		return (0);
	else
	{
		while (s[i])
		{
			d[i] = s[i];
			i++;
		}
		d[i] = '\0';
		return (d);
	}
}
