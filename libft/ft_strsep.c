/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 12:41:27 by thakala           #+#    #+#             */
/*   Updated: 2021/11/28 16:31:15 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsep(char **stringp, const char *delim)
{
	char	*beginning;

	beginning = *stringp;
	if (!beginning)
		return (beginning);
	*stringp = ft_strpbrk(*stringp, delim);
	if (*stringp)
		*(*stringp)++ = '\0';
	return (beginning);
}
