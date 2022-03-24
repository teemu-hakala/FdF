/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:04:44 by thakala           #+#    #+#             */
/*   Updated: 2021/12/11 09:22:06 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpop(t_list *head, t_list *remove, void (*del)(void *c, size_t s))
{
	t_list	*previous;
	t_list	*iterator;
	t_list	*next;

	iterator = head;
	while (iterator && iterator != remove)
	{
		previous = iterator;
		iterator = iterator->next;
	}
	next = NULL;
	if (iterator == remove)
	{
		next = iterator->next;
		del(iterator->content, iterator->content_size);
	}
	previous->next = next;
	return (previous);
}
/*
t_list	*ft_lstpop(t_list *previous)
{
	t_list	*remove;
	t_list	*next;

	remove = previous->next;
	next = NULL;
	if (remove)
		next = remove->next;
	previous->next = next;
	return (previous);
}
*/
