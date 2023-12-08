/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:11:12 by tiaferna          #+#    #+#             */
/*   Updated: 2023/12/08 12:11:57 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	is_white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	lexer_elements(char const *s)
{
	size_t	i;
	size_t	elements;

	i = 0;
	elements = 0;
	while (s[i])
	{
		while ((s[i] == '\"' && s[i + 1] == '\"') || (s[i] == '\'' && s[i + 1] == '\''))
			i += 2;
		if (!is_white_space(s[i]) && s[i])
			elements++;
		while (!is_white_space(s[i]) && s[i])
		{
			if (s[i] == '\"' || s[i] == '\'')
			{
				i++;
				while (s[i] != '\"' && s[i] != '\'' && s[i])
					i++;
				if (s[i] == '\"' || s[i] == '\'')
					continue ;
			}
			i++;
		}
		while (is_white_space(s[i]) && s[i])
			i++;
	}
	return (elements);
}

static int	lexer_size_of_word(char const *s, int i)
{
	size_t	len;

	len = 0;
	while (s[i + len] && !is_white_space(s[i + len]) && s[i + len] != '\"' && s[i + len] != '\'')
		len++;
	return (len);
}

static int	lexer_quoted_size_of_word(char const *s, int i, char **arr)
{
	size_t	len;
	char	quote;
	
	len = 0;
	quote = s[i- 1];
	if (!s[i])
	{
		ft_free_smatrix(arr);
		quotes_error();
	}
	while (s[i + len] && s[i + len] != quote)
	{
		if (!s[i + len + 1] && s[i + len] != quote)
		{
			ft_free_smatrix(arr);
			quotes_error();
		}
		len++;
	}
	return (len);
}

void	create_token(char const *s, char	**arr, size_t *i, size_t *j)
{
	while (s[*i])
	{
		while (is_white_space(s[*i]))
			*i += 1;
		if (s[*i] == '\0')
			break ;
		if ((s[*i] == '\"' && s[*i + 1] == '\"') || (s[*i] == '\'' && s[*i + 1] == '\''))
		{
			*i += 2;
			continue ;
		}
		if ((s[*i] == '\"' || s[*i] == '\'') && s[*i])
		{
			arr[*j] = ft_substr(s, ++*i, lexer_quoted_size_of_word(s, *i, arr));
			arr[*j][lexer_quoted_size_of_word(s, *i, arr)] = '\0';
			*i += lexer_quoted_size_of_word(s, *i, arr) + 1;
		}
		else if (s[*i])
		{
			arr[*j] = ft_substr(s, *i, lexer_size_of_word(s, *i));
			arr[*j][lexer_size_of_word(s, *i)] = '\0';
			*i += lexer_size_of_word(s, *i);
		}
		*j += 1;
	}
}

char	**lexer_split(char const *s)
{
	size_t	i;
	size_t	j;
	char	**arr;

	i = 0;
	j = 0;
	if (lexer_elements(s) == 0)
		return NULL;
	arr = malloc(sizeof(char *) * (lexer_elements(s) + 1));
	if (!arr)
		return (NULL);
	while (s[i])
		create_token(s, arr, &i, &j);
	arr[j] = NULL;
	return (arr);
}
