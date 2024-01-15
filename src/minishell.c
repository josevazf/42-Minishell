/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:06:33 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/15 17:47:49 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"
#include "../includes/parser.h"
#include "../includes/executer.h"

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
			break;
		}
		if (input[0] == '\0')
		{
			free(input);
			continue;	
		}
		quotes_checker(input);
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
