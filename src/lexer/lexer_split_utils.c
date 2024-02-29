/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:54:45 by tiago             #+#    #+#             */
/*   Updated: 2024/02/29 18:03:53 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	lexer_size_of_word(char *s, size_t *i, t_mshell *init)
{
	int		len;
	char	quote;

	len = 0;
	init->lexer->d_quote_expand = 0;
	while (s[*i] && !ft_iswhitespace(s[*i]) && \
	s[*i] != '|' && s[*i] != '>' && s[*i] != '<')
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

// char	*create_lexer_substr(size_t i, size_t len, char *s, unsigned int start)
// {
// 	if ((s[start + j] == '\'' || s[start + j] == '\"') && flag == 0)
// 	{
// 		flag = 1;
// 		quote = s[start + j];
// 		j++;
// 	}
// 	if (s[start + j] == quote && flag)
// 	{
// 		j++;
// 		flag = 0;
// 		continue ;
// 	}
// 	substr[i] = s[start + j];
// 	i++;
// 	j++;
	
// }

char	*ft_lexer_substr(char *s, unsigned int start, size_t len, char *substr)
{
	char	quote;
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
		if ((s[start + j] == '\'' || s[start + j] == '\"') && quote == 0)
			quote = s[start + j++];
		if (s[start + j] == quote)
		{
			j++;
			quote = 0;
			continue ;
		}
		substr[i++] = s[start + j++];
	}
	substr[i] = '\0';
	return (substr);
}
