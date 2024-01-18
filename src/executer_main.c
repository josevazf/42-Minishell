/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:26:40 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/18 18:41:45 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/parser.h"

int	exit_code;

void	get_exit_code(int status)
{
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = WTERMSIG(status);
	else if (WIFSTOPPED(status))
		exit_code = WSTOPSIG(status);
	else
		printf("Something strange just happened.\n");
}

void	fork_pipe(t_parser *parser_node, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;

	if (pipe(pipe_fd) == -1)
		ft_error("minishell: failed creating pipe", ERROR); /* FIXXXXX */
	pid = fork();
	if (pid == -1)
		ft_error("minishell: failed creating fork", ERROR); /* FIXXXXX */
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		execve(parser_node->path_exec, parser_node->cmd_exec, envp);
	}
	else
	{
		close(pipe_fd[1]);
		if (waitpid(pid, &status, 0) != -1 )
			get_exit_code(status);
        else
		{
            perror("waitpid() failed"); //corrigir
            exit(EXIT_FAILURE);
        }
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
}

void 	fork_cmd(t_parser *parser_node, char **envp)
{
	pid_t		pid;
	int			status;
	
	pid = fork();
	if (pid == -1)
		ft_error("minishell: failed creating fork", ERROR);
	if (pid == 0)
		execve(parser_node->path_exec, parser_node->cmd_exec, envp);
	else
	{
        if (waitpid(pid, &status, 0) != -1 )
			get_exit_code(status);
        else
		{
            perror("waitpid() failed"); //corrigir
            exit(EXIT_FAILURE);
        }
	}
}

/* TOOOOO DOOOOOOOOOOOOOO */
void	executer_router(t_mshell *init, char **envp)
{
	t_parser	*parser_node;
	int			og_stdin;

	init->nbr_pipes = 0;
	get_pipes(init);
	if (init->nbr_pipes == 0)
		fork_cmd(init->parser, envp);
	else
	{
		og_stdin = dup(STDIN_FILENO);
		parser_node = init->parser;
		while (init->nbr_pipes > 0)
		{
			fork_pipe(parser_node, envp);
			parser_node = parser_node->next;
			init->nbr_pipes--;		
		}
		fork_cmd(parser_node, envp);
		dup2(og_stdin, STDIN_FILENO);
		//free(parser_node);
	}
}

void	executer_main(t_mshell *init, char **envp)
{
	char		**strings_env;
	
	//i = -1;
	if (init->cmd_not_found)
	{
		exit_code = 127;
		init->parser = NULL;
		return ;
	}
	strings_env = convert_env(init);
	executer_router(init, envp);
/* 	while (strings_env[++i])
		ft_printf("%s", strings_env[i]); */
	ft_free_smatrix(strings_env);
}
