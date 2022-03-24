/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 19:55:30 by thakala           #+#    #+#             */
/*   Updated: 2021/11/29 21:52:30 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *c, size_t s))
{
	t_list	*upcoming;
	t_list	*current;

	current = *alst;
	while (current)
	{
		upcoming = current->next;
		if (current)
			ft_lstdelone(&current, del);
		current = upcoming;
	}
	*alst = NULL;
}
