/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:38:59 by thakala           #+#    #+#             */
/*   Updated: 2021/12/12 17:21:30 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	l_dst;

	l_dst = ft_strlen(dst);
	if (l_dst >= dstsize)
		return (ft_strlen(src) + dstsize);
	while (*src && dstsize - l_dst - 1)
		dst[l_dst++] = *src++;
	dst[l_dst] = '\0';
	while (*src++)
		l_dst++;
	return (l_dst);
}
