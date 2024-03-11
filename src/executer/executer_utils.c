/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:05:37 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/03/11 09:00:36 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Get here_doc input and write to pipe */
void	write_here_doc(t_mshell *init, char *eof, int *pipe_fd, int *exit_code)
{
	char	*input;

	ft_putstr_fd("> ", init->og_stdout);
	input = get_next_line(init->og_stdin);
	heredoc_expander(init, &input, exit_code);
	free_expander(init->exp);
	if (!input)
	{
		perror("minishell: input error");
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (ft_strlen(input) == (ft_strlen(eof) + 1) && \
		ft_strncmp(input, eof, ft_strlen(eof)) == 0)
	{
		free(input);
		close(pipe_fd[1]);
		exit(EXIT_SUCCESS);
	}
	write(pipe_fd[1], input, ft_strlen(input));
	free(input);
}

/* Process here_doc */
int	process_here_doc(t_mshell *init, char *eof, int *exit_code)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		export;
	int		status;

	if (pipe(pipe_fd) == -1)
		ft_error("minishell: failed creating pipe", ERROR);
	pid = fork();
	if (pid == -1)
		ft_error("minishell: failed creating fork", ERROR);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		while (1)
			write_here_doc(init, eof, pipe_fd, exit_code);
	}
	else
	{
		close(pipe_fd[1]);
		export = dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		waitpid(pid, &status, 0);
		return (export);
	}
}

/* Get number of pipes */
void	get_pipes(t_mshell *init)
{
	t_lexer	*lexer;

	lexer = init->lexer;
	while (lexer)
	{
		if (lexer->operator == PIPE)
			init->nbr_pipes++;
		lexer = lexer->next;
	}
	free(lexer);
}

/* Convert Env linked list to original format `**char` */
char	**convert_env(t_mshell *init)
{
	char	**strings_env;
	char	*temp_line;
	t_env	*env_table;

	env_table = init->env_table;
	temp_line = ft_strdup("");
	while (env_table)
	{
		temp_line = ft_strupdate(temp_line, env_table->var);
		temp_line = ft_strupdate(temp_line, "=");
		temp_line = ft_strupdate(temp_line, env_table->content);
		temp_line = ft_strupdate(temp_line, "\t");
		env_table = env_table->next;
	}
	strings_env = ft_split(temp_line, '\t');
	free(temp_line);
	free(env_table);
	return (strings_env);
}

void	executer_cmd_router(t_mshell *init, t_parser *parser_node,
			char ***envp, int *exit_code)
{
	if (!ft_strcmp(parser_node->cmd_exec[0], "echo"))
		echo(parser_node, 2, 1);
	else if (!ft_strcmp(parser_node->cmd_exec[0], "cd"))
		cd(init, parser_node, exit_code, envp);
	else if (!ft_strcmp(parser_node->cmd_exec[0], "pwd"))
		pwd(parser_node);
	else if (!ft_strcmp(parser_node->cmd_exec[0], "export"))
	{
		export(init, envp, exit_code);
		exit(EXIT_SUCCESS);
	}
	else if (!ft_strcmp(parser_node->cmd_exec[0], "unset"))
		unset(init, envp);
	else if (!ft_strcmp(parser_node->cmd_exec[0], "env"))
	{
		if (!parser_node->cmd_exec[1])
			env(init);
		printf("env: '%s': No such file or directory\n", 
			parser_node->cmd_exec[1]);
		exit(127);
	}
	else
		execve(parser_node->path_exec, parser_node->cmd_exec, *envp);
}
