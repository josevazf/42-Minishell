/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:34:48 by patatoss          #+#    #+#             */
/*   Updated: 2024/01/10 17:43:53 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"
#include "../includes/parser.h"

/* Free Parser nodes */
void	free_parser(t_mshell *init)
{
	t_parser	*temp_parser;
	
	while (init->parser)
	{
		temp_parser = init->parser;
		ft_free_smatrix(init->parser->cmd_exec);
		free(init->parser->path_exec);
		init->parser->cmd_type = 0;
		init->parser->input = 0;
		init->parser->output = 0;
		init->parser = init->parser->next;
		free(temp_parser);
	}
}

/* Free Env table */
void	free_env(t_mshell *init)
{
	t_env	*temp_env;

	while (init->env_table)
	{
		temp_env = init->env_table;
		free(init->env_table->var);
		free(init->env_table->content);
		init->env_table = init->env_table->next;
		free(temp_env);
	}
}

/* Free Lexer tokens */
void	free_lexer(t_mshell *init)
{
	t_lexer	*temp_lex;
	
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
}

void	delete_lists(t_mshell *init)
{
	if (init->lexer)
		free_lexer(init);
	if (init->env_table)
		free_env(init);
	if (init->parser)
		free_parser(init);
}
