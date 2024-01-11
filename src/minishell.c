/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patatoss <patatoss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:06:33 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/10 13:37:24 by patatoss         ###   ########.fr       */
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
		mshell_init(init);
		init->input = ft_strdup(input);
		free(input);
		create_env_list(init, envp, 0);
		// print_env(init); // PRINT ENV TABLE
		lexer_main(init);
		//print_lexer(init); // PRINT LEXER TOKENS
		parser_main(init, init->lexer, NULL, 0);
		//print_parser(init); // PRINT PARSER NODES
		executer_main(init, envp);
		delete_lists(init);
	}
	(void)argv;
	return (0);
}
