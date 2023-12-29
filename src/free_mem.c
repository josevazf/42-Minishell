/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:34:48 by patatoss          #+#    #+#             */
/*   Updated: 2023/12/29 09:05:51 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	delete_lists(t_mshell *init)
{
	t_lexer	*temp_lex;
	t_env	*temp_env;

	while (init->lexer)
	{
		temp_lex = init->lexer;
		free(init->lexer->str);
		init->lexer->operator = 0;
		init->lexer->i = 0;
		init->lexer->prev = NULL;
		init->lexer = init->lexer->next;
		free(temp_lex);
	}
	while (init->env_table)
	{
		temp_env = init->env_table;
		free(init->env_table->var);
		free(init->env_table->content);
		init->env_table = init->env_table->next;
		free(temp_env);
	}
}
