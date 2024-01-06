/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:06:55 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/06 19:06:51 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

/* Prints Parser node */
void	print_node(t_parser *parser)
{
	int i;
	
	i = -1;
	ft_printf("cmd->");
	while (parser->cmd_exec[++i])
		ft_printf("%s ", parser->cmd_exec[i]);
	ft_printf("\n");
	ft_printf("path->%s\n", parser->path_exec);
	ft_printf("type->%d\n", parser->cmd_type);
	ft_printf("input->%d\n", parser->input);
	ft_printf("output->%d\n\n", parser->output);
}

t_parser	*create_parser_node(int cmd_type, char *cmd_temp, char *cmd_path)
{
	t_parser	*node;

	node = (t_parser *)malloc(sizeof(t_parser));
	if (!node)
		return (NULL);
	node->cmd_type = cmd_type;
	node->cmd_exec = ft_split(cmd_temp, '\n');
	node->path_exec = ft_strdup(cmd_path);
	node->input = STDIN_FILENO;
	node->output = STDOUT_FILENO;
	node->next = NULL;
	//print_node(node);
	return (node);
}

void	parser_node_push_back(t_parser **begin_list, int cmd_type, 
		char *cmd_temp, char *cmd_path)
{
	t_parser	*node;
	
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

/* void	parser_main(t_mshell *init, int i)
{
	int			cmd_type;
	char		*cmd_temp;
	char		*cmd_temp2;
	char		*cmd_path;
	t_parser	*parser;

	parser = NULL;
	while (init->lexer && ++i)
	{
		if (init->lexer->operator == PIPE)
			init->lexer = init->lexer->next;
		cmd_type = cmd_router(init->lexer->str);
		cmd_path = find_cmd(init->lexer->str);
		cmd_temp = ft_strdup(init->lexer->str);
		init->lexer = init->lexer->next;
		while (init->lexer && init->lexer->operator != PIPE)
		{
			cmd_temp2 = ft_strjoin(cmd_temp, "\n");
			free(cmd_temp);
			cmd_temp = ft_strjoin(cmd_temp2, init->lexer->str);
			free(cmd_temp2);
			init->lexer = init->lexer->next;
		}
		if (!parser)
			parser = create_parser_node(cmd_type, cmd_temp, cmd_path);
		else if (init->lexer && init->lexer->operator != PIPE)
			parser_node_push_back(&parser, cmd_type, cmd_temp, cmd_path);
		free(cmd_path);
		free(cmd_temp);
	}
	init->parser = parser;
} */

void	parser_main(t_mshell *init, int i)
{
	int			cmd_type;
	char		*cmd_temp;
	char		*cmd_temp2;
	char		*cmd_path;
	t_parser	*parser;
	t_lexer		*lexer;
	
	lexer = init->lexer;
	while (lexer && ++i)
	{
		//ft_printf("i---->%d.\n", i);
		//ft_printf("operator---->%d\n", lexer->operator);
		if (lexer->operator == PIPE)
		{
			//ft_printf("ok\n");
			lexer = lexer->next;
			//ft_printf("operator---->%d\n", lexer->operator);
		}
		cmd_type = cmd_router(lexer->str);
		cmd_path = find_cmd(lexer->str);
		cmd_temp = ft_strdup(lexer->str);
		lexer = lexer->next;
		while (lexer && lexer->operator != PIPE)
		{
			cmd_temp2 = ft_strjoin(cmd_temp, "\n");
			free(cmd_temp);
			cmd_temp = ft_strjoin(cmd_temp2, lexer->str);
			free(cmd_temp2);
			lexer = lexer->next;
		}
		if (i == 1)
			parser = create_parser_node(cmd_type, cmd_temp, cmd_path);
		else
			parser_node_push_back(&parser, cmd_type, cmd_temp, cmd_path);
		free(cmd_path);
		free(cmd_temp);
	}
	init->parser = parser;
	free(lexer);
}