/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:06:33 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/06 19:06:57 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"
#include "../includes/parser.h"

int		main(int argc, char **argv, char **envp)
{
	char 		*input;
	t_mshell	*init;
	
	if (argc != 1)
		args_error();
	while (1)
	{
		input = readline("minishell$> ");
		if (input == NULL) // Resolve o CTLR+D
		{
			ft_printf("Exiting...\n");
			break;
		}
		if (input[0] == '\0')
		{
			free(input);
			continue;	
		}
		quotes_checker(input); // coloquei esta verificacao logo apos a funcao readline para evitar avancar no programa caso o input tenha falta de quote(s) - Tiago
		init = (t_mshell *)malloc(sizeof(t_mshell));
		create_env_list(init, envp, 0);
		//print_env(init); // PRINT ENV TABLE
		lexer_main(init, input);
		//print_lexer(init); // PRINT LEXER TOKENS
		//env(init);
		//export(init);
		//ft_printf("\n\n\n");
		//env(init);
		parser_main(init, 0);
		print_parser(init); // PRINT PARSER NODES
		free(input);
		delete_lists(init);
		free(init);
	}
	(void)argv;
	return (0);
}
