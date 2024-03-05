/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:22:15 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/03/05 00:12:28 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_parser(t_mshell *init)
{
	int			i;
	t_parser	*parser;

	parser = init->parser;
	while (parser != NULL)
	{
		i = -1;
		if (parser->cmd_exec)
		{
			printf("cmd->");
			while (parser->cmd_exec[++i])
				printf("%s ", parser->cmd_exec[i]);
		}
		else
			ft_printf("cmd-> NULL");
		printf("\n");
		printf("path-> %s\n", parser->path_exec);
		if (parser->redirs)
			printf("redirs-> %s\n", parser->redirs);
		printf("input-> %d\n", parser->input);
		printf("output-> %d\n\n", parser->output);
		parser = parser->next;
	}
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
}

/* Prints Env table */
void	print_env(t_mshell *init)
{
	t_env	*env_table;

	env_table = init->env_table;
	while (env_table)
	{
		ft_printf("%s=", env_table->var);
		ft_printf("%s\n", env_table->content);
		env_table = env_table->next;
	}
}
