/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:11:12 by tiaferna          #+#    #+#             */
/*   Updated: 2023/12/19 12:17:59 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	quotes_checker(char const *s)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			s_quote++;
			i++;
			while (s[i] != '\'' && s[i])
				i++;
			if (s[i] && s[i] == '\'')
				s_quote++;
		}
		else if (s[i] == '\"')
		{
			d_quote++;
			i++;
			while (s[i] != '\"' &&s[i])
				i++;
			if (s[i] && s[i] == '\"')
				d_quote++;
		}
		i++;
	}
	if (s_quote % 2 != 0 || d_quote % 2 != 0)
		quotes_error();
	return ;
}

void	lexer_elements_aid(char const *s, size_t *i)
{
	char quote;
	
	while (!ft_iswhitespace(s[*i]) && s[*i])
	{
		if (s[*i] == '\'' || s[*i] == '\"')
		{
			quote = s[(*i)++];
			while (s[*i] != quote && s[*i])
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
	ft_printf("returned elements : %d\n", elements); // TEST
	return (elements);
}

static int	lexer_size_of_word(char const *s, size_t *i) // REVER
{
	int	len;
	// size_t	ignore_quote;
	char	quote;
	
	len = 0;
	// ignore_quote = 0;
	while (!ft_iswhitespace(s[*i]) && s[*i])
	{
		if (s && (*s == '\'' || *s == '\"'))
		{
			quote = s[*i];
			ft_printf("quote = %c\n", quote);
			while (s[*i] && s[++(*i)] != quote)
				len++;
		}
		else
		{
			while (s[*i] && !ft_iswhitespace(s[(*i)++]))
				len++;
		}
		ft_printf("s[*i] = %c\n", s[*i]);
	}
	return (len /* - ignore_quote */);
}

char	*ft_lexer_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 1;
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	if (ft_strlen(s) < start)
		len = 0;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	while (i < len)
	{
		// if (s[start + j] != '\'' && s[start + j] != '\"')
		// {
		substr[i] = s[start + j];
		i++;
		// }
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
		ft_printf("j = %d\n", *j);
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
			len = lexer_size_of_word(s, i);
			ft_printf("len = %d\n", len);
			arr[*j] = ft_lexer_substr(s, *i - len - 1, len);
			arr[*j][len] = '\0';
			if (s[*i] == '\"' || s[*i] == '\'')
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
	quotes_checker(s);
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
