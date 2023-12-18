/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:11:12 by tiaferna          #+#    #+#             */
/*   Updated: 2023/12/18 13:10:12 by tiaferna         ###   ########.fr       */
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

static int	lexer_quoted_size_of_word(char const *s, size_t *i, char **arr)
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
			quote++;
		len++;
	}
	return (len - quote);
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
			arr[*j] = ft_substr(s, (*i), lexer_quoted_size_of_word(s, i, arr)); //CRIAR NOVA FUNCAO PARA IGNORAR OS QUOTES QUANDO CRIA A SUBSTRING
			arr[*j][lexer_quoted_size_of_word(s, i, arr)] = '\0';
			*i += lexer_quoted_size_of_word(s, i, arr) + 1;
			if (s[*i] == '\"' || s[*i] == '\'')
				(*i)++;
			(*i)++;
			ft_printf("%d\n", *i);
		}
		// else if (s[*i])
		// {
		// 	arr[*j] = ft_substr(s, *i, lexer_size_of_word(s, *i));
		// 	arr[*j][lexer_size_of_word(s, *i)] = '\0';
		// 	*i += lexer_size_of_word(s, *i);
		// }
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
	ft_printf("elements: %d\n", lexer_elements(s) + 1);
	arr = malloc(sizeof(char *) * (lexer_elements(s) + 1));
	if (!arr)
		return (NULL);
	while (s[i])
		create_token(s, arr, &i, &j);
	arr[j] = NULL;
	i = 0;
	while (arr[i])
	{
		ft_printf("3%s\n", arr[i++]);
	}
	return (arr);
}
