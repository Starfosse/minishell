/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouleau <abouleau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:29:59 by abouleau          #+#    #+#             */
/*   Updated: 2021/11/29 13:21:04 by abouleau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in_charset(char c, char b)
{
	if (c == b)
		return (1);
	return (0);
}

int	count_words(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && is_in_charset(str[i], c))
			i++;
		if (str[i])
			count++;
		while (str[i] && !is_in_charset(str[i], c))
			i++;
	}
	return (count);
}

int	word_lenght(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && !is_in_charset(str[i], c))
	{
		i++;
		count++;
	}
	return (count);
}

int	ft_strndup(char **dest, char const *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	*dest = (char *)malloc(sizeof(char) * (n + 1));
	if (!*dest)
		return (0);
	while (i < n && src[i])
	{
		(*dest)[i] = src[i];
		i++;
	}
	while (i < n)
	{
		(*dest)[i] = '\0';
		i++;
	}
	(*dest)[i] = '\0';
	return (n);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		number_word;
	int		word_len;
	char	**tab;

	i = 0;
	j = -1;
	if (!s)
		return (NULL);
	number_word = count_words(s, c);
	tab = (char **)malloc(sizeof(char *) * (number_word + 1));
	if (!tab)
		return (NULL);
	while (++j < number_word)
	{
		while (s[i] && is_in_charset(s[i], c))
			i++;
		word_len = word_lenght(s + i, c);
		i += ft_strndup(&tab[j], s + i, word_len);
		if (!tab[j])
			return (NULL);
	}
	tab[j] = NULL;
	return (tab);
}
