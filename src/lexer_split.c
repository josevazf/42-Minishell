/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patatoss <patatoss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:11:12 by tiaferna          #+#    #+#             */
/*   Updated: 2024/01/07 17:29:06 by patatoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

int	lexer_size_of_word(char *s, size_t *i, t_mshell *init)
{
	int		len;
	char	quote;

	len = 0;
	init->lexer->d_quote_expand = 0;
	quote = '\"';
	while (!ft_iswhitespace(s[*i]) && s[*i])
	{
		if (s && (s[*i] == '\'' || s[*i] == '\"'))
		{
			quote = s[*i];
			len++;
			(*i)++;
			while (s[*i] && s[*i] != quote)
			{
				if (s[*i] == '$' && quote == '\'')
					init->lexer->d_quote_expand = 1;
				(*i)++;
				len++;
			}
		}
		len++;
		(*i)++;
	}
	return (len);
}

size_t	len_update(char *s, unsigned int start, size_t len)
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

char	*ft_lexer_substr(char *s, unsigned int start, size_t len)
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

void	create_token(t_mshell *init, size_t *i)
{
	size_t	len;
	t_lexer	*lexer_head;
	
	len = 0;
	lexer_head = NULL;
	while (init->input[*i])
	{
		if (!init->lexer)
			init->lexer = (t_lexer *)malloc(sizeof(t_lexer));
		init->lexer->str = NULL;
		init->lexer->next = NULL;
		if (!lexer_head)
			lexer_head = init->lexer;
		while (ft_iswhitespace(init->input[*i]) && init->input[*i])
			(*i)++;
		while (init->input[*i] && ((init->input[*i] == '\"' && init->input[*i + 1] == '\"') || \
		(init->input[*i] == '\'' && init->input[*i + 1] == '\'')))
			*i += 2;
		if (init->input[*i] && !ft_iswhitespace(init->input[*i]))
		{
			len = lexer_size_of_word(init->input, i, init);
			init->lexer->str = ft_lexer_substr(init->input, *i - len, len);
			if (init->input[*i] && (init->input[*i] == '\"' || init->input[*i] == '\''))
				(*i)++;
		}
		if (init->input[*i])
			init->lexer->next = (t_lexer *)malloc(sizeof(t_lexer));
		init->lexer = init->lexer->next;
	}
	init->lexer = lexer_head;
}

void	lexer_split(t_mshell *init)
{
	size_t	i;
	
	i = 0;
	quotes_checker(init->input);
	if (lexer_elements(init->input) == 0)
		return ; // falta adicionar tratamento de erro
	init->lexer = NULL;
	create_token(init, &i);
	return ;
}
