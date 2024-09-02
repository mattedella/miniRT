/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:35:49 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/28 16:36:14 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *buff, int c)
{
	int	i;

	if (buff == NULL)
		return (NULL);
	i = 0;
	while (buff[i])
	{
		if (buff[i] == (char)c)
			return ((char *)&buff[i]);
		i++;
	}
	if (buff[i] == (char)c)
		return ((char *)&buff[i]);
	return (0);
}
