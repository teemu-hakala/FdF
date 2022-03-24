/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 05:38:53 by thakala           #+#    #+#             */
/*   Updated: 2021/11/26 12:04:39 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (!n)
		return (0);
	while (*((unsigned char *)s1++) == *((unsigned char *)s2++) && --n)
		;
	return ((int)(*((unsigned char *)s1 - 1) - *((unsigned char *)s2 - 1)));
}
