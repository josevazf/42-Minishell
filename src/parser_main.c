/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:06:55 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/02 23:38:56 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_parser	*create_parser_node(int cmd_type, char *cmd_temp, char *cmd_path)
{
	t_parser	*node;

	node = malloc(sizeof(t_parser));
	if (!node)
		return (NULL);
	node->cmd_type = cmd_type;
	node->cmd_exec = ft_split(cmd_temp, "\n");
	node->path_exec = ft_strdup(cmd_path);
	node->input = STDIN_FILENO;
	node->output = STDOUT_FILENO;
	node->next = NULL;
	return (node);
}

void	parser_node_push_back(t_parser **begin_list, int cmd_type, char *cmd_temp, char *cmd_path)
{
	t_env	*node;
	
	node = *begin_list;
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = create_parser_node(cmd_type, cmd_temp, cmd_path);
	}
	else
		*begin_list = create_parser_node(cmd_type, cmd_temp, cmd_path);
}

void	parser_main(t_mshell *init)
{
	int			i;
	int			cmd_type;
	char		*cmd_temp;
	char		*cmd_path;
	t_parser	*parser;

	i = -1;
	while (init->lexer)
	{
		i++;
		cmd_type = cmd_router(init->lexer->str);
		cmd_path = find_cmd(init->lexer->str);
		cmd_temp = ft_strjoin("\0", init->lexer->str);
		while (init->lexer && init->lexer->operator != PIPE)
		{
			init->lexer = init->lexer->next;
			cmd_temp = ft_strjoin(cmd_temp, "\n");
			cmd_temp = ft_strjoin(cmd_temp, init->lexer->str);
		}
		if (i == 0)
			parser = create_parser_node(cmd_type, cmd_temp, cmd_path);
		else
			parser_node_push_back(&parser, cmd_type, cmd_temp, cmd_path);
	}
	free(cmd_path);
}
