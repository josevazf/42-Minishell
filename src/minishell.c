/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:06:33 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/02/16 18:01:06 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signo;

void	minishell(int exit_code, char **envp)
{
	char 		*input;
	char		*dir;
	char		**envp_copy;
	t_mshell	*init;

	envp_copy = envp_dup(envp);
	while (1)
	{
		dir = ft_strdup("\033[1;32m");
		dir = ft_strupdate(dir, "Minishell:~");
		dir = ft_strupdate(dir, getcwd(NULL, 0));
		dir = ft_strupdate(dir, "\033[0m$ ");
		set_signals();
		input = readline(dir);
		free(dir);
		if (input == NULL || ft_strcmp(input, "exit") == 0)
		{
			printf("exit\n");
			break ;
		}
		if (input[0] == '\0' || quotes_checker(input) != 0)
		{
			if (quotes_checker(input) != 0)
				printf("minishell: unclosed quotes\n");
			free(input);
			continue ;	
		}
		add_history(input);
		init = (t_mshell *)malloc(sizeof(t_mshell));
		mshell_init(init);
		init->in = ft_strdup(input);
		free(input);
		create_env_list(init, envp_copy, 0);
		// print_env(init); // PRINT ENV TABLE
		lexer_main(init, &exit_code);
		if (ft_strlen(init->in) > 0)
		{
			// print_lexer(init); // PRINT LEXER TOKENS
			parser_main(init, NULL, NULL, NULL);
			// print_parser(init); // PRINT PARSER NODES
			executer_main(init, &exit_code, &envp_copy);
		}
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
