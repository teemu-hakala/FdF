/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:03:12 by thakala           #+#    #+#             */
/*   Updated: 2021/12/08 11:00:47 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

static size_t	ft_intlen(int n)
{
	size_t		l;

	l = 0;
	if (n <= 0)
		l++;
	while (n)
	{
		n /= 10;
		l++;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	char	*numeral;
	size_t	n_len;

	n_len = ft_intlen(n);
	numeral = (char *)malloc(sizeof(*numeral) * (n_len + 1));
	if (!numeral)
		return (NULL);
	numeral[n_len] = '\0';
	if (n < 0)
	{
		*numeral = '-';
		numeral[--n_len] = '0' + -(n % 10);
		n /= -10;
	}
	else if (n == 0)
		numeral[--n_len] = '0';
	while (n)
	{
		numeral[--n_len] = '0' + n % 10;
		n /= 10;
	}
	return (numeral);
}
