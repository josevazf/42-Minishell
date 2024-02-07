/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:26:40 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/02/06 20:02:48 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_exit_code(int status, int *exit_code)
{
	if (WIFEXITED(status))
		*exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*exit_code = WTERMSIG(status);
	else if (WIFSTOPPED(status))
		*exit_code = WSTOPSIG(status);
	else
		printf("Something strange just happened.\n");
}

void	fork_pipe(t_parser *parser_node, char **strings_env, int *exit_code)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		ft_error("minishell: failed creating pipe", ERROR); /* FIXXXXX */
	pid = fork();
	if (pid == -1)
		ft_error("minishell: failed creating fork", ERROR); /* FIXXXXX */
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], parser_node->output);
		close(pipe_fd[1]);
		if (parser_node->cmd_exec != NULL)
			execve(parser_node->path_exec, parser_node->cmd_exec, strings_env);
	}
	else
		fork_pipe_utils(pipe_fd, pid, exit_code, &parser_node);

}

void 	fork_cmd(t_parser *parser_node, char **strings_env, int *exit_code)
{
	pid_t		pid;
	int			status;
	
	pid = fork();
	if (pid == -1)
		ft_error("minishell: failed creating fork", ERROR);
	if (pid == 0 && parser_node->cmd_exec != NULL)
	{
		execve(parser_node->path_exec, parser_node->cmd_exec, strings_env);
		close(pid);
	}
	else
	{
        if (waitpid(pid, &status, 0) != -1 )
			get_exit_code(status, exit_code);
        else
		{
            perror("waitpid() failed yoyoyo"); //corrigir
            exit(EXIT_FAILURE);
        }
	}
}

/* Fix env file */
void	executer_router(t_mshell *init, char **strings_env, int *exit_code)
{
	t_parser	*parser_node;

	init->nbr_pipes = 0;
	get_pipes(init);
	if (init->nbr_pipes == 0)
		fork_cmd(init->parser, strings_env, exit_code);
	else
	{
		parser_node = init->parser;
		while (init->nbr_pipes > 0)
		{
			fork_pipe(parser_node, strings_env, exit_code);
			parser_node = parser_node->next;
			init->nbr_pipes--;		
		}
		fork_cmd(parser_node, strings_env, exit_code);
	}
	dup2(init->og_stdin, STDIN_FILENO);
	dup2(init->og_stdout, STDOUT_FILENO);
	close(init->og_stdin);
	close(init->og_stdout);
}

void	executer_main(t_mshell *init, int *exit_code)
{
	char		**strings_env;

	signal(SIGINT, sighandler_fork);
	signal(SIGQUIT, sighandler_fork);
	if (init->cmd_not_found)
	{
		*exit_code = 127;
		init->parser = NULL;
		return ;
	}
	strings_env = convert_env(init);
	executer_router(init, strings_env, exit_code);
/* 	while (strings_env[++i])
		ft_printf("%s", strings_env[i]); */
	ft_free_smatrix(strings_env);
}