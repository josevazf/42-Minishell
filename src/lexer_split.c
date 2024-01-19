/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:11:12 by tiaferna          #+#    #+#             */
/*   Updated: 2024/01/19 15:02:00 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_token(t_mshell *init, size_t *i)
{
	size_t	len;

	len = 0;
	len = lexer_size_of_word(init->input, i, init);
	init->lexer->str = ft_lexer_substr(init->input, *i - len, len);
	if (init->input[*i] && (init->input[*i] == '\"' || init->input[*i] == '\''))
		(*i)++;
}

void	create_all_tokens(t_mshell *init)
{
	size_t	i;
	t_lexer	*lexer_head;

	i = 0;
	lexer_head = NULL;
	while (init->input[i])
	{
		if (!init->lexer)
			init->lexer = (t_lexer *)malloc(sizeof(t_lexer));
		lexer_init(init->lexer);
		if (!lexer_head)
			lexer_head = init->lexer;
		while (ft_iswhitespace(init->input[i]) && init->input[i])
			i++;
		while (init->input[i] && ((init->input[i] == '\"' && \
		init->input[i + 1] == '\"') || (init->input[i] == '\'' \
		&& init->input[i + 1] == '\'')))
			i += 2;
		if (init->input[i] && !ft_iswhitespace(init->input[i]))
			create_token(init, &i);
		if (init->input[i])
			init->lexer->next = (t_lexer *)malloc(sizeof(t_lexer));
		init->lexer = init->lexer->next;
	}
	init->lexer = lexer_head;
}

void	lexer_split(t_mshell *init)
{
	init->lexer = NULL;
	create_all_tokens(init);
	return ;
}
