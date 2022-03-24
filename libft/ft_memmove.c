/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:35:21 by thakala           #+#    #+#             */
/*   Updated: 2021/12/16 20:11:46 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = (size_t)(-1);
	if (src < dst)
		while (--len + 1)
			((char *)dst)[len] = ((char *)src)[len];
	else if (src > dst)
		while (++i < len)
			((char *)dst)[i] = ((char *)src)[i];
	return (dst);
}
