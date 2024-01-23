/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:06:55 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/23 21:57:13 by jrocha-v         ###   ########.fr       */
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
	ft_printf("type->%d\n", parser->cmd_type);
	ft_printf("input->%d\n", parser->input);
	ft_printf("output->%d\n\n", parser->output);
}

t_parser	*create_parser_node(char **cmd_full, char *cmd_path, \
											int input, int output)
{
	t_parser	*node;

	node = (t_parser *)malloc(sizeof(t_parser));
	if (!node)
		return (NULL);
	node->cmd_exec = cmd_full;
	node->path_exec = ft_strdup(cmd_path);
	node->input = input;
	node->output = output;
	node->next = NULL;
	//print_node(node);
	return (node);
}

void	parser_node_push_back(t_parser **begin_list, char **cmd_full, 
								char *cmd_path, int input, int output)
{
	t_parser	*node;
	
	node = *begin_list;
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = create_parser_node(cmd_full, cmd_path, input, output);
	}
	else
		*begin_list = create_parser_node(cmd_full, cmd_path, input, output);
}

t_parser	*parser_node(t_mshell *init, t_parser *parser, char *redirs, 
								char *cmds)
{
	char		*cmd_path;
	char		**cmd_full;
	
	(void)redirs;
	if (cmds)
	{
		ft_printf("cmds: %s\n", cmds);
		ft_printf("redirs: %s\n", redirs);
		cmd_full = ft_split(cmds, '\t');
		if ((cmd_path = find_cmd(cmd_full[0], init)) == NULL)
			return (NULL);
	}
	if (!parser)
		parser = create_parser_node(cmd_full, cmd_path, STDIN_FILENO, STDOUT_FILENO);
	else
		parser_node_push_back(&parser, cmd_full, cmd_path, STDIN_FILENO, STDOUT_FILENO);
	free_parser_temps(cmds, cmd_path);
	init->parser = parser;
	return (parser);
}

char	*parser_merge_split(char *og_str, char *lexer_str)
{
	og_str = ft_strupdate(og_str, "\t");
	og_str = ft_strupdate(og_str, lexer_str);
	og_str = ft_strupdate(og_str, "\t");
	return (og_str);
}

void	parser_main(t_mshell *init, t_parser *parser, char *redirs, char *cmds)
{
	t_lexer		*lexer;

	lexer = init->lexer;
	(void)redirs;
	while (lexer)
	{
		if (lexer->operator == PIPE)
			lexer = lexer->next;
		while (lexer && lexer->operator != PIPE)
		{
			if(lexer->operator >= 3 && lexer->operator <= 6 && !redirs)
			{
				redirs = ft_strdup(lexer->str);
				lexer = lexer->next;
				redirs = parser_merge_split(redirs, lexer->str);
			}
			else if (lexer->operator >= 3 && lexer->operator <= 6)
			{
				redirs = ft_strupdate(redirs, lexer->str);
				lexer = lexer->next;
				redirs = ft_strupdate(redirs, lexer->str);
				lexer = lexer->next;
			}
			if (lexer->operator == CMD && !cmds)
			{
				cmds = ft_strdup(lexer->str);
				lexer = lexer->next;
			}
			if (lexer->operator == CMD)
			{
				cmds = parser_merge_split(cmds, lexer->str);
				lexer = lexer->next;
			}
		}
		parser = parser_node(init, parser, redirs, cmds);
	}
	free(lexer);
}

// OG
/* void	parser_main(t_mshell *init, t_lexer *lexer, t_parser *parser, int cmd_type)
{
	char		*cmd_temp;
	char		*cmd_path;
	
	while (lexer)
	{
		if (lexer->operator == PIPE)
			lexer = lexer->next;
		cmd_type = cmd_router(lexer->str);
		if ((cmd_path = find_cmd(lexer->str, init)) == NULL)
			return ;			
		cmd_temp = ft_strdup(lexer->str);
		while ((lexer = lexer->next) && lexer->operator != PIPE)
		{
			cmd_temp = ft_strupdate(cmd_temp, "\n");
			cmd_temp = ft_strupdate(cmd_temp, lexer->str);
		}
		if (!parser)
			parser = create_parser_node(cmd_type, cmd_temp, cmd_path);
		else
			parser_node_push_back(&parser, cmd_type, cmd_temp, cmd_path);
		free_parser_temps(cmd_path, cmd_temp);
	}
	init->parser = parser;
	free(lexer);
} */