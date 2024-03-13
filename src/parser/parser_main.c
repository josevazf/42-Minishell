/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:06:55 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/03/13 16:49:21 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Fill parser node */
t_parser	*create_parser_node(t_mshell *init, char *cmds, t_parser *node)
{
	node = (t_parser *)malloc(sizeof(t_parser));
	if (!node)
		return (NULL);
	if (!cmds)
	{
		node->cmd_exec = NULL;
		node->path_exec = NULL;
	}
	else
	{
		node->cmd_exec = ft_split(cmds, '\t');
		node->path_exec = ft_strdup(init->tcmd_path);
		node->cmd_type = cmd_router(node->cmd_exec[0]);
	}
	if (!init->tredirs)
		node->redirs = NULL;
	else
		node->redirs = ft_strdup(init->tredirs);
	node->input = init->red_input;
	node->output = init->red_output;
	node->next = NULL;
	node->token_err = false;
	node->file_nf = false;
	return (node);
}

/* Set new parser node to the end of the parser linked list */
void	parser_node_push_back(t_mshell *init, t_parser **begin_list,
			char *cmds, t_parser *node)
{
	node = *begin_list;
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = create_parser_node(init, cmds, NULL);
	}
	else
		*begin_list = create_parser_node(init, cmds, NULL);
}

/* Route information to create new parser node */
t_parser	*parser_node_router(t_mshell *init, char ***envp_copy,
				t_parser *parser, char *cmds)
{
	init->tcmd_full = NULL;
	init->tcmd_path = NULL;
	if (cmds)
	{
		init->tcmd_full = ft_split(cmds, '\t');
		init->tcmd_path = find_cmd(init->tcmd_full[0], init, envp_copy);
	}
	if (!parser)
		parser = create_parser_node(init, cmds, NULL);
	else
		parser_node_push_back(init, &parser, cmds, NULL);
	free_parser_temps(cmds, init->tredirs, init->tcmd_path, init->tcmd_full);
	init->parser = parser;
	return (parser);
}

int	check_pipe_syntax(t_mshell *init, t_lexer *lexer)
{
	lexer = init->lexer;
	while (lexer)
	{
		if (lexer->operator == PIPE)
		{
			if (!lexer->next || lexer->next->operator == PIPE \
				|| !lexer->prev || !ft_strncmp(lexer->str, "||", 2))
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				init->stop_exec = true;
				return (ERROR);
			}
			else if (lexer->next->operator == PIPE && \
				lexer->next->next->operator == PIPE)
			{
				printf("minishell: syntax error near unexpected token `||'\n");
				init->stop_exec = true;
				return (ERROR);
			}
		}
		lexer = lexer->next;
	}
	return (SUCCESS);
}

void	parser_main(t_mshell *init, char ***envp_copy, t_parser *parser,
			char *cmds)
{
	t_lexer		*lexer;

	if (check_pipe_syntax(init, NULL) == 1 || check_redir_syntax(init) == 1)
		return ;
	lexer = init->lexer;
	while (lexer)
	{
		if (lexer->operator == PIPE)
			lexer = lexer->next;
		while (lexer && lexer->operator != PIPE)
		{
			if (lexer->operator >= 3 && lexer->operator <= 6)
				init->tredirs = get_redirs(init, init->tredirs, &lexer);
			else if (lexer->operator == CMD && !cmds)
				cmds = ft_strdup(lexer->str);
			else if (lexer->operator == CMD)
				cmds = parser_merge_split(cmds, lexer->str);
			lexer = lexer->next;
		}
		parser = parser_node_router(init, envp_copy, parser, cmds);
		if (parser == NULL)
			lexer = NULL;
		free_parser_vars(&cmds, &init->tredirs);
	}
	free(lexer);
}
