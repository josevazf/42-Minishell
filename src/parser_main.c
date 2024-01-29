/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:06:55 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/29 20:01:38 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Prints Parser node: TO DELETE EVENTUALLLYYYYYY!!!!!!!!!!!!!!!!!!*/
void	print_node(t_parser *parser)
{
	int i;
	
	i = -1;
	ft_printf("cmd->");
	while (parser->cmd_exec[++i])
		ft_printf("%s ", parser->cmd_exec[i]);
	ft_printf("\n");
	ft_printf("path->%s\n", parser->path_exec);
	ft_printf("input->%d\n", parser->input);
	ft_printf("output->%d\n\n", parser->output);
}

t_parser	*create_parser_node(t_mshell *init, char *cmds, char *cmd_path)
{
	t_parser	*node;

	node = (t_parser *)malloc(sizeof(t_parser));
	if (!node)
		return (NULL);
	node->cmd_exec = ft_split(cmds, '\t');
	node->path_exec = ft_strdup(cmd_path);
	node->input = init->red_input;
	node->output = init->red_output;
	node->next = NULL;
	//print_node(node);
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
	char		**redirs_full;
	
	if (cmds)
	{
		cmd_full = ft_split(cmds, '\t');
		cmd_path = find_cmd(cmd_full[0], init);
		if (cmd_path == NULL)
		{
			free_parser_temps(cmds, redirs, cmd_path, cmd_full);
			if (parser)
				free_parser(parser);
			return (NULL);
		}
	}
	if (redirs)
	{
		redirs_full = ft_split(redirs, '\t');
		if (!ft_strncmp(redirs_full[0], "<", 1))
			init->red_input = process_file(init, redirs_full[1], IN_FILE);
		if (!ft_strncmp(redirs_full[0], "<<", 1))
			init->red_input = process_here_doc(init, redirs_full[1]);
		if (!ft_strncmp(redirs_full[0], ">>", 2))
			init->red_output = process_file(init, redirs_full[1], OUT_FILE_APND);
		else if (!ft_strncmp(redirs_full[0], ">", 1))
			init->red_output = process_file(init, redirs_full[1], OUT_FILE_OWR);
		ft_free_smatrix(redirs_full);
		
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
	}
	free(lexer);
}
