/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 09:36:55 by thakala           #+#    #+#             */
/*   Updated: 2021/11/20 09:40:05 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memdup(const void *memory, size_t size)
{
	void	*duplicate;

	duplicate = malloc(size);
	if (duplicate)
		ft_memcpy(duplicate, memory, size);
	return (duplicate);
}
