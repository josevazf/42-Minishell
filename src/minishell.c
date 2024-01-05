/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patatoss <patatoss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:06:33 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/04 16:19:49 by patatoss         ###   ########.fr       */
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
	input = readline("minishell$> ");
	if (ft_strlen(input) == 0)
	{
		free(input);
		ft_printf("Tente novamente\n");
		return (0);
	}
	quotes_checker(input); // coloquei esta verificacao logo apos a funcao readline para evitar avancar no programa caso o input tenha falta de quote(s) - Tiago
	init = (t_mshell *)malloc(sizeof(t_mshell));
	create_env_list(init, envp, 0);
	//print_env(init); // PRINT ENV TABLE
	lexer_main(init, input);
	env(init);
	export(init);
	ft_printf("\n\n\n");
	env(init);
	// parser_main(init);
	//print_lexer(init); // PRINT LEXER TOKENS
	parser_main(init, 0);
	//print_parser(init); // PRINT PARSER NODES
	free(input);
	delete_lists(init);
	free(init);
	(void)argv;
	return (0);
}
