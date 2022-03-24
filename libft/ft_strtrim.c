/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:25:19 by thakala           #+#    #+#             */
/*   Updated: 2021/11/18 10:02:23 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_is_whitespace(const char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

static size_t	ft_strlen_trim(const char *s, int (*f)(char))
{
	size_t		len;
	size_t		whitespace_count;

	len = 0;
	whitespace_count = 0;
	while (*s)
	{
		if (f(*s++))
			whitespace_count++;
		else
			whitespace_count = 0;
		len++;
	}
	return (len - whitespace_count);
}

char	*ft_strtrim(char const *s)
{
	size_t	trimmed_len;
	char	*trimmed_str;

	while (*s && ft_is_whitespace(*s))
		s++;
	trimmed_len = ft_strlen_trim(s, &ft_is_whitespace);
	trimmed_str = (char *)malloc(sizeof(char) * (trimmed_len + 1));
	if (!trimmed_str)
		return (NULL);
	ft_strncpy(trimmed_str, s, trimmed_len)[trimmed_len] = '\0';
	return (trimmed_str);
}
