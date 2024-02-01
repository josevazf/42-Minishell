/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:11:12 by tiaferna          #+#    #+#             */
/*   Updated: 2024/01/30 17:53:25 by tiago            ###   ########.fr       */
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

void	create_all_tokens(t_mshell *init)
{
	size_t	i;
	t_lexer	*lexer_head;

	i = 0;
	lexer_head = NULL;
	while (init->in[i])
	{
		if (!init->lexer)
			init->lexer = (t_lexer *)malloc(sizeof(t_lexer));
		lexer_init(init->lexer);
		if (!lexer_head)
			lexer_head = init->lexer;
		while (ft_iswhitespace(init->in[i]) && init->in[i])
			i++;
		while (init->in[i] && ((init->in[i] == '\"' && \
		init->in[i + 1] == '\"') || (init->in[i] == '\'' \
		&& init->in[i + 1] == '\'')))
			i += 2;
		if (init->in[i] && !ft_iswhitespace(init->in[i]))
			create_token(init, &i);
		if (init->in[i])
			init->lexer->next = (t_lexer *)malloc(sizeof(t_lexer));
		init->lexer = init->lexer->next;
	}
	init->lexer = lexer_head;
}

void	check_empty_node(t_mshell *init)
{
	t_lexer	*node;
	
	node = init->lexer;
	while (node->next)
	{
		if (node->next->str == NULL)
		{
			free(node->next);
			node->next = NULL;
			break ;
		}
		node = node->next;
	}
}

void	lexer_split(t_mshell *init)
{	
	init->lexer = NULL;
	create_all_tokens(init);
	check_empty_node(init);
	return ;
}
