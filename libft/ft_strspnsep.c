/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspnsep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:54:16 by thakala           #+#    #+#             */
/*   Updated: 2021/12/06 14:23:14 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strspnsep(char **stringp, const char *delim)
{
	char	*beginning;

	beginning = *stringp;
	if (!beginning)
		return (beginning);
	*stringp = ft_strpbrk(*stringp, delim);
	if (*stringp)
	{
		*(*stringp)++ = '\0';
		*stringp += ft_strspn(*stringp, delim);
		if (!**stringp)
			*stringp = NULL;
	}
	return (beginning);
}
