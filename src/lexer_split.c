/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patatoss <patatoss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:11:12 by tiaferna          #+#    #+#             */
/*   Updated: 2023/12/21 13:27:46 by patatoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

int	lexer_size_of_word(char const *s, size_t *i)
{
	int		len;
	char	quote;

	len = 0;
	while (!ft_iswhitespace(s[*i]) && s[*i])
	{
		if (s && (s[*i] == '\'' || s[*i] == '\"'))
		{
			quote = s[*i];
			len++;
			(*i)++;
			while (s[*i] && s[*i] != quote)
			{
				(*i)++;
				len++;
			}
		}
		len++;
		(*i)++;
	}
	return (len);
}

size_t	len_update(char const *s, unsigned int start, size_t len)
{
	size_t	updated_len;
	char	quote;

	updated_len = len;
	len += start;
	while (start < len)
	{
		if (s[start] == '\'' || s[start] == '\"')
		{
			quote = s[start];
			start++;
			while (s[start] != quote && start < len)
				start++;
			updated_len -= 2;
		}
		start++;
	}
	return (updated_len);
}

char	*ft_lexer_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len = len_update(s, start, len);
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	while (i < len)
	{
		if (s[start + j] == '\'' || s[start + j] == '\"')
			j++;
		if (s[start + j] != '\'' && s[start + j] != '\"')
		{
			substr[i] = s[start + j];
			i++;
		}
		j++;
	}
	substr[i] = '\0';
	return (substr);
}

void	create_token(char const *s, char **arr, size_t *i, size_t *j)
{
	size_t	len;

	len = 0;
	while (s[*i])
	{
		while (ft_iswhitespace(s[*i]) && s[*i])
			(*i)++;
		while (s[*i] && ((s[*i] == '\"' && s[*i + 1] == '\"') || \
		(s[*i] == '\'' && s[*i + 1] == '\'')))
			*i += 2;
		if (s[*i] && !ft_iswhitespace(s[*i]))
		{
			len = lexer_size_of_word(s, i);
			arr[*j] = ft_lexer_substr(s, *i - len, len);
			if (s[*i] && (s[*i] == '\"' || s[*i] == '\''))
				(*i)++;
			*j += 1;
		}
	}
}

char	**lexer_split(char const *s)
{
	size_t	i;
	size_t	j;
	char	**arr;

	i = 0;
	j = 0;
	quotes_checker(s);
	if (lexer_elements(s) == 0)
		return (NULL);
	arr = malloc(sizeof(char *) * (lexer_elements(s) + 1));
	if (!arr)
		return (NULL);
	while (s[i])
		create_token(s, arr, &i, &j);
	arr[j] = NULL;
	return (arr);
}
