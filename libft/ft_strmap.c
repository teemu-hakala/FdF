/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:49:18 by thakala           #+#    #+#             */
/*   Updated: 2021/11/29 21:50:31 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char c))
{
	char	*new_beginning;
	size_t	length;

	length = ft_strlen(s);
	new_beginning = (char *)malloc(sizeof(char) * (++length));
	if (new_beginning)
	{
		new_beginning[--length] = '\0';
		while (--length + 1)
			new_beginning[length] = f(s[length]);
	}
	return (new_beginning);
}
