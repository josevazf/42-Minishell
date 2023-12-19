/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:06:33 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/12/19 12:19:00 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		main(int argc, char **argv, char **envp)
{
	char 		*input;
	t_mshell	*init;
	
	if (argc != 1)
		args_error();
	init = (t_mshell *)malloc(sizeof(t_mshell));
	init->env_table = create_envll(envp);
	input = readline("minishell$> ");
	lexer_main(input, envp);
	while (init->env_table)
	{
		printf("%s\t", init->env_table->var);
		printf("%s\n", init->env_table->content);
		init->env_table = init->env_table->next;
	}
	(void)argv;
	(void)envp;
	return (0);
}
