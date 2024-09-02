/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:22:44 by mdella-r          #+#    #+#             */
/*   Updated: 2023/11/08 11:23:17 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}

void del(void *content)
{
	free(content);
}

int main()
{
	t_list	*node = malloc(sizeof(t_list));
	if (node == NULL)
	{
		printf("malloc fallita");
		return (1);
	}
	node->content=strdup("ciao");
	node->next=NULL;
	printf("prima : %s\n", (char *)node->content);
	ft_lstdelone(node, del);
	printf("dopo : %s\n", (char *)node->content);
	return (0);
}