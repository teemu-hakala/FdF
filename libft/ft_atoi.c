/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:19:47 by thakala           #+#    #+#             */
/*   Updated: 2021/12/08 14:42:14 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	char	coefficient;
	long	result;

	while (ft_isspace(*str))
		str++;
	coefficient = 1;
	if (*str == '+' || *str == '-')
		coefficient = -(*str++ - 44);
	result = 0;
	while (*str == '0')
		str++;
	while (ft_isdigit(*str))
	{
		result = 10 * result + coefficient * (*str++ - '0');
		if (((result >> 63) | 0x1) != coefficient)
		{
			if (coefficient == -1)
				return (0);
			return (-1);
		}
	}
	return ((int)result);
}
