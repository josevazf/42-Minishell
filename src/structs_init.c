/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:44:03 by patatoss          #+#    #+#             */
/*   Updated: 2024/02/29 17:22:21 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_table_init(t_env *env_table)
{
	env_table->var = NULL;
	env_table->content = NULL;
	env_table->visibility = 0;
	env_table->next = NULL;
}

void	expander_init(t_expand *expander)
{
	expander->i = 0;
	expander->macro_len = 0;
	expander->s_quote = 1;
	expander->d_quote = 1;
	expander->new_input = NULL;
}

void	lexer_init(t_lexer *lexer)
{
	lexer->str = NULL;
	lexer->operator = 0;
	lexer->i = 0;
	lexer->d_quote_expand = 0;
	lexer->is_node = 0;
	lexer->next = NULL;
	lexer->prev = NULL;
}

void	parser_init(t_parser *parser)
{
	parser->cmd_exec = NULL;
	parser->path_exec = NULL;
	parser->redirs = NULL;
	parser->file_nf = false;
	parser->token_err = false;
	parser->cmd_type = 0;
	parser->input = 0;
	parser->output = 0;
	parser->next = NULL;
}

void	mshell_init(t_mshell *init)
{
	init->in = NULL;
	init->nbr_pipes = 0;
	init->tcmd_full = NULL;
	init->tcmd_path = NULL;
	init->tredirs = NULL;
	init->temp_pid = 0;
	init->cmd_index = 0;
	init->og_stdin = dup(STDIN_FILENO);
	init->og_stdout = dup(STDOUT_FILENO);
	init->red_input = STDIN_FILENO;
	init->red_output = STDOUT_FILENO;
	init->stop_redirs = false;
	init->env_table = NULL;
	init->exp = NULL;
	init->lexer = NULL;
	init->parser = NULL;
}
