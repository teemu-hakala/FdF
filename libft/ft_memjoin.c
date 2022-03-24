/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:53:02 by thakala           #+#    #+#             */
/*   Updated: 2021/12/08 20:06:40 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memjoin(const void *mem1, const void *mem2,
	size_t len1, size_t len2)
{
	char	*result;

	result = (char *)malloc(sizeof(char) * (len1 + len2));
	if (!result)
		return (NULL);
	while (len2--)
		result[len1 + len2] = ((char *)mem2)[len2];
	while (len1--)
		result[len1] = ((char *)mem1)[len1];
	return (result);
}
