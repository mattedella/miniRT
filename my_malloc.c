/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:30:50 by mdella-r          #+#    #+#             */
/*   Updated: 2024/09/02 17:28:43 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

void	*my_calloc(size_t size)
{
	t_list	*node;
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	node = ft_lstnew(ptr);
	ft_lstadd_front(garbage_collector(), node);
	return (ptr);
}

t_list	**garbage_collector(void)
{
	static t_list	*gc = NULL;

	return (&gc);
}

void	garbage_collector_free(void)
{
	t_list	*node;
	t_list	*tmp;

	node = *garbage_collector();
	while (node)
	{
		tmp = node->next;
		if (node)
		{
			if (node->content)
				free(node->content);
			free(node);
		}
		node = tmp;
	}
	*garbage_collector() = NULL;
}
