/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:11:12 by tiaferna          #+#    #+#             */
/*   Updated: 2024/03/18 10:13:31 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_token(t_mshell *init, size_t *i)
{
	size_t	len;

	len = 0;
	if ((init->in[*i] == '<' && init->in[*i + 1] == '<' ) || \
	(init->in[*i] == '>' && init->in[*i + 1] == '>' ))
	{
		len = 2;
		*i += 2;
	}
	else if (init->in[*i] == '|' || init->in[*i] == '<' || init->in[*i] == '>')
	{
		len = 1;
		(*i)++;
	}
	else
		len = lexer_size_of_word(init->in, i, init);
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
		init->lexer->next->prev = init->lexer->next;
		init->lexer = init->lexer->next;
	}
}

void	create_all_tokens(t_mshell *init)
{
	size_t	i;
	t_lexer	*lexer_head;

	i = 0;
	lexer_head = NULL;
	while (init->in[i])
	{
		while (ft_iswhitespace(init->in[i]) && init->in[i])
			i++;
		malloc_tokens(init, i);
		if (!lexer_head)
			lexer_head = init->lexer;
		if (init->in[i] && (ft_iswhitespace(init->in[i + 2])) \
				&& ((init->in[i] == '\"' && init->in[i + 1] == '\"')
				|| (init->in[i] == '\'' && init->in[i + 1] == '\'')))
		{
			init->lexer->str = ft_strdup("\'\'");
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
	create_all_tokens(init);
	return ;
}
