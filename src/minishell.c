/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:06:33 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/02/28 15:42:46 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signo;


char	*prompt_line(char **envp_copy)
{
	char	*line;
	char	*dir;
	char	*cwd;
	int		i;
	int		len;
	
	i = 0;
	len = 0;
	while (envp_copy[i] && ft_strncmp(envp_copy[i], "HOME", 4) != 0)
		i++;
	if (envp_copy[i])
		len = ft_strlen(envp_copy[i] + 4);
	cwd = getcwd(NULL, 0);
	if (envp_copy[i] && ft_strncmp(cwd, envp_copy[i] + 5, len - 1) == 0)
		dir = ft_strdup(cwd + len - 1);
	else
		dir = ft_strdup(cwd);
	free(cwd);
	line = ft_strdup("\033[1;32mMinishell:~");
	line = ft_strupdate(line, dir);
	free(dir);
	line = ft_strupdate(line, "\033[0m$ ");
	return (line);
}

void	minishell(int exit_code, char **envp)
{
	char 		*input;
	char		*line;
	char		**envp_copy;
	t_mshell	*init;

	envp_copy = envp_dup(envp);

	while (1)
	{
		line = prompt_line(envp_copy);
		set_signals();
		input = readline(line);
		free(line);
		if (input == NULL || ft_strcmp(input, "exit") == 0)
		{
			printf("exit\n");
			break ;
		}
		if (input[0] == '\0' || quotes_checker(input) != 0)
		{
			if (quotes_checker(input) != 0)
			{
				add_history(input);
				printf("minishell: unclosed quotes\n");
			}
			free(input);
			continue ;	
		}
		add_history(input);
		init = (t_mshell *)malloc(sizeof(t_mshell));
		mshell_init(init);
		init->in = ft_strdup(input);
		free(input);
		create_env_list(init, envp_copy);
		// print_env(init); // PRINT ENV TABLE
		lexer_main(init, &envp_copy, &exit_code);
		if (ft_strlen(init->in) > 0)
		{
			// print_lexer(init); // PRINT LEXER TOKENS
			parser_main(init, &envp_copy, NULL, NULL);
			// print_parser(init); // PRINT PARSER NODES
			executer_main(init, &envp_copy, &exit_code);
		}
		delete_lists(init);
	}
	ft_free_smatrix(envp_copy);
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
