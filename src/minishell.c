/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:06:33 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/02/06 12:36:07 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signo;

void	minishell(int exit_code, char **envp)
{
	char 		*input;
	t_mshell	*init;

	while (1)
	{
		set_signals();
		input = readline("minishell$> ");
		if (input == NULL || ft_strcmp(input, "exit") == 0) // Resolve o CTLR+D
		{
			ft_printf("Exiting...\n");
			break ;
		}
		if (input[0] == '\0' || quotes_checker(input) != 0)
		{
			if (quotes_checker(input) != 0)
				ft_printf("minishell: unclosed quotes\n");
			free(input);
			continue ;	
		}
		add_history(input);
		init = (t_mshell *)malloc(sizeof(t_mshell));
		mshell_init(init);
		init->in = ft_strdup(input);
		free(input);
		create_env_list(init, envp, 0);
		// print_env(init); // PRINT ENV TABLE
		lexer_main(init, &exit_code);
		// print_lexer(init); // PRINT LEXER TOKENS
		parser_main(init, NULL, NULL, NULL); // WIPPPP 
		// parser_main(init, init->lexer, NULL);
		// print_parser(init); // PRINT PARSER NODES
		executer_main(init, &exit_code);
		delete_lists(init);
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	int			exit_code;
	
	exit_code = 0;
	if (argc != 1)
		args_error();
	minishell(exit_code, envp);
	(void)argv;
	return (0);
}
