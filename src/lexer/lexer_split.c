/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:11:12 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/09 13:57:23 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_token(t_mshell *init, size_t *i)
{
	size_t	len;

	len = 0;
	if (ft_strnstr(init->origin_in, init->in + *i, ft_strlen(init->origin_in)))
	{
		if ((init->in[*i] == '<' && init->in[*i + 1] == '<' ) || \
		(init->in[*i] == '>' && init->in[*i + 1] == '>' ))
		{
			len = 2;
			*i += 2;
		}
		else if (init->in[*i] == '|' || init->in[*i] == '<' \
		|| init->in[*i] == '>')
		{
			len = 1;
			(*i)++;
		}
		else
			len = lexer_size_of_word(init->in, i, init);
	}
	else
		len = special_lexer_size_of_word(init->in, i, init);
	init->lexer->str = ft_lexer_substr(init->in, *i - len, len);
	if (init->in[*i] && (init->in[*i] == '\"' || init->in[*i] == '\''))
		(*i)++;
}

void	malloc_tokens(t_mshell *init, int i)
{
	if (init->in[i] && !init->lexer)
	{
		init->lexer = (t_lexer *)malloc(sizeof(t_lexer));
		lexer_init(init->lexer);
	}
	else if (init->in[i] && !init->lexer->next)
	{
		init->lexer->next = (t_lexer *)malloc(sizeof(t_lexer));
		lexer_init(init->lexer->next);
		init->lexer->next->prev = init->lexer;
		init->lexer = init->lexer->next;
	}
}

void	create_all_tokens(t_mshell *init, size_t i)
{
	t_lexer	*lexer_head;
	size_t	in_len;

	lexer_head = NULL;
	in_len = ft_strlen(init->in);
	while (init->in[i])
	{
		while (ft_iswhitespace(init->in[i]) && init->in[i])
			i++;
		malloc_tokens(init, i);
		if (!lexer_head)
			lexer_head = init->lexer;
		if (i < in_len - 1 && (ft_iswhitespace(init->in[i + 2])) \
				&& ((init->in[i] == '\"' && init->in[i + 1] == '\"')
				|| (init->in[i] == '\'' && init->in[i + 1] == '\'')))
		{
			// if (init->is_echo == false)
			// 	init->lexer->str = ft_strdup("''");
			i += 2;
		}
		else if (init->in[i] && !ft_iswhitespace(init->in[i]))
			create_token(init, &i);
	}
	init->lexer = lexer_head;
}

void	lexer_split(t_mshell *init)
{
	init->lexer = NULL;
	// if (ft_strnstr(init->in, "echo", ft_strlen(init->in)) != NULL)
		// init->is_echo = true;
	create_all_tokens(init, 0);
	free(init->origin_in);
	return ;
}
