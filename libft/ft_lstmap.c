/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:24:51 by mdella-r          #+#    #+#             */
/*   Updated: 2023/10/23 12:14:21 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*t;
	t_list	*ti;

	t = malloc(sizeof(t_list));
	if (lst == NULL || t == NULL || f == NULL || del == NULL)
		return (NULL);
	t->content = f(lst->content);
	t->next = NULL;
	ti = t;
	lst = lst->next;
	while (lst != NULL)
	{
		t->next = malloc(sizeof(t_list));
		if (t->next == NULL)
		{
			ft_lstclear(&ti, del);
			return (ti);
		}
		t = t->next;
		t->content = f(lst->content);
		t->next = NULL;
		lst = lst->next;
	}
	return (ti);
}
