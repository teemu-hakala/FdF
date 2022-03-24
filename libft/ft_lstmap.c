/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 13:35:44 by thakala           #+#    #+#             */
/*   Updated: 2021/12/16 20:09:24 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_erase_node(void *content, size_t content_size)
{
	ft_bzero(content, content_size);
	free(content);
}

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*head;
	t_list	*current;

	current = f(lst);
	if (!current)
		return (NULL);
	head = current;
	lst = lst->next;
	while (lst)
	{
		current->next = f(lst);
		if (!current->next)
		{
			ft_lstdel(&head, ft_erase_node);
			return (NULL);
		}
		current = current->next;
		lst = lst->next;
	}
	return (head);
}
