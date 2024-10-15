/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:30:50 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/11 11:58:35 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_list	**garbage_collector(void)
{
	static t_list	*gc = NULL;

	return (&gc);
}

void	*my_calloc(size_t size, int n_cmd)
{
	t_list	*node;
	void	*ptr;

	ptr = ft_calloc(n_cmd, size);
	if (!ptr)
		return (NULL);
	node = ft_lstnew(ptr);
	ft_lstadd_front(garbage_collector(), node);
	return (ptr);
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

int	control_object(char **tmp)
{
	if (ft_strncmp(tmp[0], "sp", 3) == 0)
		return (0);
	else if (ft_strncmp(tmp[0], "pl", 3) == 0)
		return (0);
	else if (ft_strncmp(tmp[0], "cy", 3) == 0)
		return (0);
	return (1);
}

void	get_nbr_object(t_minirt *data, int i, int j, int k)
{
	data->nbr_object = i + j + k;
	data->nbr_plane = j;
	data->nbr_sphere = i;
	data->nbr_cylinder = k;
}
