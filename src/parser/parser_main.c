/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:06:55 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/02/12 16:41:52 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_parser	*create_parser_node(t_mshell *init, char *cmds, char *cmd_path)
{
	t_parser	*node;

	node = (t_parser *)malloc(sizeof(t_parser));
	if (!node)
		return (NULL);
	if (!cmds || init->stop_redirs)
	{
		node->cmd_exec = NULL;
		node->path_exec = NULL;		
	}
	else
	{
		node->cmd_exec = ft_split(cmds, '\t');
		node->path_exec = ft_strdup(cmd_path);	
	}
	node->input = init->red_input;
	node->output = init->red_output;
	node->next = NULL;
	return (node);
}

void	parser_node_push_back(t_mshell *init, t_parser **begin_list, char *cmds, 
								char *cmd_path)
{
	t_parser	*node;

	node = *begin_list;
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = create_parser_node(init, cmds, cmd_path);
	}
	else
		*begin_list = create_parser_node(init, cmds, cmd_path);
}

t_parser	*parser_node_router(t_mshell *init, t_parser *parser, char *redirs, 
								char *cmds)
{
	char		*cmd_path;
	char		**cmd_full;
	
	cmd_path = NULL;
	cmd_full = NULL;
	if (redirs)
		redirs_router(init, redirs);
	if (cmds)
	{
		cmd_full = ft_split(cmds, '\t');
		cmd_path = find_cmd(cmd_full[0], init);
		if (cmd_path == NULL)
		{
			free_parser_temps(cmds, redirs, cmd_path, cmd_full);
			free_parser(parser);
			return (NULL);
		}
	}
	if (!parser)
		parser = create_parser_node(init, cmds, cmd_path);
	else
		parser_node_push_back(init, &parser, cmds, cmd_path);
	free_parser_temps(cmds, redirs, cmd_path, cmd_full);
	init->parser = parser;
	return (parser);
}

void	parser_main(t_mshell *init, t_parser *parser, char *redirs, char *cmds)
{
	t_lexer		*lexer;

	lexer = init->lexer;
	while (lexer)
	{
		if (lexer->operator == PIPE)
			lexer = lexer->next;
		while (lexer && lexer->operator != PIPE)
		{
			if (lexer->operator >= 3 && lexer->operator <= 6)
				redirs = get_redirs(redirs, &lexer);
			else if (lexer->operator == CMD && !cmds)
				cmds = ft_strdup(lexer->str);
			else if (lexer->operator == CMD)
				cmds = parser_merge_split(cmds, lexer->str);
			lexer = lexer->next;
		}
		parser = parser_node_router(init, parser, redirs, cmds);
		if (parser == NULL)
			lexer = NULL;
		free_parser_vars(&cmds, &redirs);
		init->stop_redirs = false;
	}
	free(lexer);
}
