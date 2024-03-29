/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 07:52:03 by tiaferna          #+#    #+#             */
/*   Updated: 2024/03/29 13:16:59 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lexer_router(t_lexer *tokens)
{
	while (tokens)
	{
		if (!tokens->str)
			tokens->operator = CMD;
		else if (!ft_strcmp(tokens->str, "|"))
			tokens->operator = PIPE;
		else if (!ft_strcmp(tokens->str, ">"))
			tokens->operator = OUT_OWR;
		else if (!ft_strcmp(tokens->str, ">>"))
			tokens->operator = OUT_APND;
		else if (!ft_strcmp(tokens->str, "<"))
			tokens->operator = IN_READ;
		else if (!ft_strcmp(tokens->str, "<<"))
			tokens->operator = IN_HDOC;
		else
			tokens->operator = CMD;
		tokens = tokens->next;
	}
}

int	lexer_main(t_mshell *init, char ***envp_copy, int *exit_code)
{
	t_lexer	*lex_node;

	if (g_signo == 130)
		*exit_code = 130;
	eof_manager(init);
	expander(init, exit_code);
	free_expander(init->exp);
	if (ft_strlen(init->in) > 0)
	{
		lexer_split(init);
		lexer_router(init->lexer);
		if (new_var_checker(init, envp_copy) == 0)
			return (1);
	}
	lex_node = init->lexer;
	while (lex_node)
	{
		if (ft_strlen(lex_node->str) == 0 && init->is_echo == false)
		{
			free(lex_node->str);
			lex_node->str = ft_strdup("''");
		}
		lex_node = lex_node->next;
	}
	return (0);
}
