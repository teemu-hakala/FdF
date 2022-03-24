/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:02:00 by thakala           #+#    #+#             */
/*   Updated: 2021/11/28 19:02:19 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strspn(const char *s, const char *charset)
{
	size_t	span;
	size_t	c;
	char	found;

	span = 0;
	--s;
	while (1)
	{
		++s;
		c = 0;
		found = 0;
		while (*s && charset[c])
		{
			if (charset[c++] == *s)
			{
				++span;
				found = 1;
				break ;
			}
		}
		if (!found || !*s)
			return (span);
	}
}
