/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:11:12 by tiaferna          #+#    #+#             */
/*   Updated: 2023/12/19 08:48:12 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	lexer_elements_aid(char const *s, size_t *i)
{
	while (!ft_iswhitespace(s[*i]) && s[*i])
	{
		if (s[*i] == '\"' || s[*i] == '\'')
		{
			(*i)++;
			while (s[*i] != '\"' && s[*i] != '\'' && s[*i])
				(*i)++;
			if (!s[*i])
				quotes_error();
			if (s[*i] == '\"' || s[*i] == '\'')
				(*i)++;
			while (!ft_iswhitespace(s[*i]) && s[*i])
				(*i)++;
		}
		(*i)++;
	}
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
		if (!ft_iswhitespace(s[i]) && s[i])
			elements++;
		lexer_elements_aid(s, &i);
		while (ft_iswhitespace(s[i]) && s[i])
			i++;
	}
	return (elements);
}

static int	lexer_size_of_word(char const *s, size_t *i, char **arr)
{
	size_t	len;
	size_t	quote;
	
	(void)arr;
	len = 0;
	quote = 0;
	if (!s[*i])
	{
		// ft_free_smatrix(arr);
		quotes_error();
	}
	while (s[*i + len] && !ft_iswhitespace(s[*i + len]))
	{
		if (s[*i + len] == '\"' || s[*i + len] == '\'')
			break ;
		if (s[*i + len] == '\"' || s[*i + len] == '\'')
			quote++;
		len++;
	}
	return (len - quote);
}

char	*ft_lexer_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	if (ft_strlen(s) < start)
		len = 0;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	while (i < len)
	{
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

void	create_token(char const *s, char	**arr, size_t *i, size_t *j)
{
	while (s[*i])
	{
		while (ft_iswhitespace(s[*i]))
			(*i)++;
		if (s[*i] == '\0')
			break ;
		if ((s[*i] == '\"' && s[*i + 1] == '\"') || (s[*i] == '\'' && s[*i + 1] == '\''))
		{
			*i += 2;
			continue ;
		}
		if (s[*i])
		{
			if (s[*i] == '\"' || s[*i] == '\'')
				(*i)++;
			arr[*j] = ft_lexer_substr(s, (*i), lexer_size_of_word(s, i, arr));
			arr[*j][lexer_size_of_word(s, i, arr)] = '\0';
			*i += lexer_size_of_word(s, i, arr) + 1;
			if (s[*i] == '\"' || s[*i] == '\'')
				(*i)++;
			(*i)++;
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
	ft_printf("elements: %d\n", lexer_elements(s) + 1); //TEST
	arr = malloc(sizeof(char *) * (lexer_elements(s) + 1));
	if (!arr)
		return (NULL);
	while (s[i])
		create_token(s, arr, &i, &j);
	arr[j] = NULL;
	i = 0;
	return (arr);
}
