/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:57:14 by mdella-r          #+#    #+#             */
/*   Updated: 2023/10/31 11:05:21 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void		*a;
	long long	p;

	if (nitems == 0 || size == 0)
		return (malloc(0));
	p = (long long)nitems * (long long)size;
	if (p > 4294967295)
		return (NULL);
	a = malloc(size * nitems);
	if (a == NULL)
		return (0);
	ft_bzero(a, size * nitems);
	return (a);
}
