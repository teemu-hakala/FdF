/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrplc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 04:46:27 by thakala           #+#    #+#             */
/*   Updated: 2022/01/07 03:50:23 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memrplc(void *mem, size_t len, int target, int filler)
{
	size_t	idx;
	void	*spot;

	idx = 0;
	while (1)
	{
		spot = ft_memchr(mem + idx, target, len - idx);
		if (!spot)
			break ;
		*(char *)spot = (char)filler;
		idx = (size_t)(spot - mem) + 1;
	}
	return (mem);
}
