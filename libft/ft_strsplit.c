/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:09:08 by thakala           #+#    #+#             */
/*   Updated: 2021/12/12 17:36:38 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_count_words(const char *string, const char delimiter)
{
	size_t	words;

	words = 0;
	words += *string != delimiter;
	while (*string && *(string + 1))
		words += (*string++ == delimiter && *string != delimiter);
	words += !words;
	return (words);
}

static void	ft_fill_word(char *word, const char delimiter, const char **s_ptr)
{
	while (**s_ptr && **s_ptr != delimiter)
		*word++ = *(*s_ptr)++;
	*word = '\0';
}

static char	*ft_get_next_word(const char **s_ptr, const char delimiter)
{
	char	*word;
	size_t	word_length;

	word_length = 0;
	while (**s_ptr && **s_ptr == delimiter)
		*s_ptr += 1;
	while ((*s_ptr)[word_length] && (*s_ptr)[word_length] != delimiter)
		word_length++;
	word = (char *)malloc(sizeof(char) * (word_length + 1));
	if (!word)
		return (NULL);
	ft_fill_word(word, delimiter, s_ptr);
	return (word);
}

static void	*free_all(char **words, size_t count)
{
	while (count + 1 > 0)
		free(words[count--]);
	free(words);
	return (NULL);
}

char	**ft_strsplit(char const *s, char c)
{
	size_t	word_count;
	size_t	i;
	char	**words;

	word_count = ft_count_words(s, c);
	words = (char **)malloc(sizeof(*words) * (word_count + 1));
	if (!words)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		words[i] = ft_get_next_word(&s, c);
		if (!words[i])
			return (free_all(words, i - 1));
		i++;
	}
	words[i] = 0;
	return (words);
}
