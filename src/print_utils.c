/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:22:15 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/19 10:03:35 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_parser(t_mshell *init)
{
	int 		i;
	t_parser	*parser;
	
	parser = init->parser;
	while (parser != NULL)
	{
		i = -1;
		ft_printf("cmd->");
		while (parser->cmd_exec[++i])
			ft_printf("%s ", parser->cmd_exec[i]);
		ft_printf("\n");
		ft_printf("path->%s\n", parser->path_exec);
		ft_printf("type->%d\n", parser->cmd_type);
		ft_printf("input->%d\n", parser->input);
		ft_printf("output->%d\n\n", parser->output);
		parser = parser->next;
	}
	free(parser);
}

/* Prints Lexer tokens */
void	print_lexer(t_mshell *init)
{
	t_lexer		*lexer;
	
	lexer = init->lexer;
	while (lexer)
	{
		ft_printf("str:%s\n", lexer->str);
		ft_printf("op:%d\n\n", lexer->operator);	
		lexer = lexer->next;
	}
	free(lexer);
}

/* Prints Env table */
void	print_env(t_mshell *init)
{
	t_env	*env_table;

	env_table = init->env_table;
	while (env_table)
	{
		ft_printf("%s->", env_table->var);
		ft_printf("%s\n", env_table->content);
		env_table = env_table->next;
	}
	free(env_table);
}
