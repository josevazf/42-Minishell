/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:06:33 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/03/04 11:38:41 by jrocha-v         ###   ########.fr       */
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
	line = ft_strdup("\033[1;32mminishell:~");
	line = ft_strupdate(line, dir);
	free(dir);
	line = ft_strupdate(line, "\033[0m$ ");
	return (line);
}

void	parse_and_execute(t_mshell *init, char ***envp_copy, int *exit_code)
{
	// print_lexer(init); // PRINT LEXER TOKENS
	parser_main(init, envp_copy, NULL, NULL);
	// print_parser(init); // PRINT PARSER NODES
	executer_main(init, envp_copy, exit_code);
}

int	minishell(int exit_code, char **envp, char *input)
{
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
		// input = check_whitespace(input);
		if (input == NULL || !ft_strncmp(input, "exit", 4))
		{
			exit_code = exit_arguments(input, exit_code);
			if (exit_code != 1 || input == NULL)
				break ;
			else
				continue;
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
		mshell_init(init, input);
		create_env_list(init, envp_copy);
		// print_env(init); // PRINT ENV TABLE
		if (lexer_main(init, &envp_copy, &exit_code) == 1)
		{
			delete_lists(init);
			continue ;
		}
		if (ft_strlen(init->in) > 0)
			parse_and_execute(init, &envp_copy, &exit_code);
		delete_lists(init);
	}
	ft_free_smatrix(envp_copy);
	rl_clear_history();
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	int			exit_code;
	
	exit_code = 0;
	if (argc != 1)
		args_error();
	exit_code = minishell(exit_code, envp, NULL);
	(void)argv;
	return (exit_code);
}
