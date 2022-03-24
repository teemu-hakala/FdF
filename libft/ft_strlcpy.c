/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 22:07:04 by thakala           #+#    #+#             */
/*   Updated: 2021/11/29 23:37:01 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	l_src;

	l_src = 0;
	if (dstsize)
	{
		while (--dstsize && src[l_src])
			*dst++ = src[l_src++];
		*dst = '\0';
	}
	while (src[l_src])
		l_src++;
	return (l_src);
}
