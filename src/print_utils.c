/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:22:15 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/03 17:41:46 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/lexer.h"
#include "../includes/parser.h"

void	print_parser(t_mshell *init)
{
	int i;
	
	i = -1;
	while (init->parser)
	{
		ft_printf("cmd->");
		while (init->parser->cmd_exec[++i])
			ft_printf("%s ", init->parser->cmd_exec[i]);
		ft_printf("\n");
		ft_printf("path->%s\n", init->parser->path_exec);
		ft_printf("type->%d\n", init->parser->cmd_type);
		ft_printf("input->%d\n", init->parser->input);
		ft_printf("output->%d\n\n", init->parser->output);
		init->env_table = init->env_table->next;
	}
}

/* Prints Lexer tokens */
void	print_lexer(t_mshell *init)
{
	while (init->lexer)
	{
		ft_printf("str:%s\n", init->lexer->str);
		ft_printf("op:%d\n\n", init->lexer->operator);	
		init->lexer = init->lexer->next;
	}
}

/* Prints Env table */
void	print_env(t_mshell *init)
{
	while (init->env_table)
	{
		ft_printf("%s->", init->env_table->var);
		ft_printf("%s\n", init->env_table->content);
		init->env_table = init->env_table->next;
	}
}
