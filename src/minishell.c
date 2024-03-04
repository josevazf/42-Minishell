/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:06:33 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/03/04 16:23:51 by jrocha-v         ###   ########.fr       */
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

void	set_prompt_and_get_input(char **envp, char **input, char **line)
{
	*line = prompt_line(envp);
	*input = readline(*line);
	free(*line);
}

void	parse_and_execute(t_mshell *init, char ***envp_copy, int *exit_code)
{
	if (ft_strlen(init->in) > 0)
	{
		// print_lexer(init); // PRINT LEXER TOKENS
		parser_main(init, envp_copy, NULL, NULL);
		// print_parser(init); // PRINT PARSER NODES
		executer_main(init, envp_copy, exit_code);
	}
	delete_lists(init);
}

void	free_and_clear(char **envp)
{
	ft_free_smatrix(envp);
	rl_clear_history();
}

int	check_whitespace(char *input)
{
	int	i;
	
	i = 0;
	if (input == NULL)
		return (EXIT_SUCCESS);
	while (input[i] && input[i] != '\0')
	{
		if (!ft_iswhitespace(input[i]) || input[i] == '\0')
			return (EXIT_SUCCESS);
		i++;
	}
	free(input);
	return (EXIT_FAILURE);
}

int	minishell(int exit_code, char **envp, char *input, char *line)
{
	t_mshell	*init;

	while (1)
	{
		set_signals();
		set_prompt_and_get_input(envp, &input, &line);
		if (check_whitespace(input) == 1)
			continue;
		if (input == NULL || !ft_strncmp(input, "exit", 4))
		{
			exit_code = exit_arguments(input, exit_code);
			if (exit_code != 1 || input == NULL)
				break ;
			continue ;
		}
		if (quotes_checker(input) != 0)
			continue ;
		init = mshell_init(init, input, envp);
		if (lexer_main(init, &envp, &exit_code) == 1)
			continue ;
		parse_and_execute(init, &envp, &exit_code);
	}
	free_and_clear(envp);
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	int			exit_code;
	char		**envp_copy;
	
	exit_code = 0;
	if (argc != 1)
		args_error();
	envp_copy = envp_dup(envp);
	exit_code = minishell(exit_code, envp_copy, NULL, NULL);
	(void)argv;
	if (exit_code < 0)
		exit_code = exit_code + 100;
	return (exit_code);
}
