/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:06:33 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/19 14:43:57 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		main(int argc, char **argv, char **envp)
{
	char 		*input;
	t_mshell	*init;
	
	if (argc != 1)
		args_error();
	while (1)
	{
		input = readline("minishell$> ");
		if (input == NULL || ft_strcmp(input, "exit") == 0) // Resolve o CTLR+D
		{
			free(input);
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
		init = (t_mshell *)malloc(sizeof(t_mshell));
		mshell_init(init);
		init->input = ft_strdup(input);
		free(input);
		create_env_list(init, envp, 0);
		// print_env(init); // PRINT ENV TABLE
		lexer_main(init);
		// print_lexer(init); // PRINT LEXER TOKENS
		parser_main(init, init->lexer, NULL, 0);
		// print_parser(init); // PRINT PARSER NODES
		executer_main(init, envp);
		delete_lists(init);
	}
	(void)argv;
	return (0);
}
