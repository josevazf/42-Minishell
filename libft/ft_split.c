/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 22:47:55 by tiaferna          #+#    #+#             */
/*   Updated: 2023/12/07 09:20:58 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	elements(char const *s, char c)
{
	size_t	i;
	size_t	elements;

	i = 0;
	elements = 0;
	while (s[i])
	{
		if (s[i] != c)
			elements++;
		while (s[i] != c && s[i])
			i++;
		while (s[i] == c && s[i])
			i++;
	}
	return (elements);
}

static int	size_of_word(char const *s, char c, int i)
{
	size_t	len;

	len = 0;
	while (s[i + len] && s[i + len] != c)
		len++;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**arr;

	i = 0;
	j = 0;
	arr = malloc(sizeof(char *) * (elements(s, c) + 1));
	if (!arr)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		arr[j] = ft_substr(s, i, size_of_word(s, c, i));
		arr[j][size_of_word(s, c, i)] = '\0';
		j++;
		i += size_of_word(s, c, i);
	}
	arr[j] = NULL;
	return (arr);
}
