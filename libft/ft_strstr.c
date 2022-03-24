/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:45:42 by thakala           #+#    #+#             */
/*   Updated: 2021/11/23 15:34:00 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	n;

	while (*haystack)
	{
		n = 0;
		while (needle[n] && haystack[n] == needle[n])
			n++;
		if (!needle[n])
			return ((char *)haystack);
		haystack++;
	}
	if (!*needle)
		return ((char *)haystack);
	return (NULL);
}
