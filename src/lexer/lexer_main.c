/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 07:52:03 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/11 12:14:43 by jrocha-v         ###   ########.fr       */
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
	if (g_signo == 130)
		*exit_code = 130;
	if (ft_strlen(init->in) > 0)
	{
		lexer_split(init);
		lexer_router(init->lexer);
		expander(init, exit_code, NULL, init->lexer);
		if (new_var_checker(init, envp_copy) == 0)
			return (1);
	}
	return (0);
}
