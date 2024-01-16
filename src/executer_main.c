/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:26:40 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/16 11:00:42 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/parser.h"
#include "../includes/minishell.h"

void	fork_pipe(t_parser *parser_node, char **envp)
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
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		execve(parser_node->path_exec, parser_node->cmd_exec, envp);
	}
	else
	{
		close(pipe_fd[1]);
		waitpid(pid, NULL, 0);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
}

void 	fork_simple(t_mshell *init, char **envp)
{
	pid_t		pid;
	t_parser	*parser;
	
	parser = init->parser;
	pid = fork();
	if (pid == -1)
		ft_error("minishell: failed creating fork", ERROR);
	if (pid == 0)
		execve(parser->path_exec, parser->cmd_exec, envp);
	else
	{
		int status;
        if (waitpid(pid, &status, 0) != -1 )
		{
            if (WIFEXITED(status) )
			{
				ft_printf("entrou 1\n");
                exit_code = WEXITSTATUS(status);
				printf("exit code = %d\n", exit_code);
			}
            else if (WIFSIGNALED(status) )
			{
				ft_printf("entrou 2\n");
                exit_code = WTERMSIG(status);
			}
            else if (WIFSTOPPED(status) )
			{
				ft_printf("entrou 3\n");
                exit_code = WSTOPSIG(status);
			}
            else
                printf("Something strange just happened.\n");
        }
        else
		{
            perror("waitpid() failed");
            exit(EXIT_FAILURE);
        }
	}
}

void	fork_router(t_mshell *init, char **envp)
{
	t_parser	*parser_node;

	init->nbr_pipes = 0;
	get_pipes(init);
	if (init->nbr_pipes == 0)
		fork_simple(init, envp);
	else
	{
		parser_node = init->parser;
		while (parser_node)
		{
			fork_pipe(parser_node, envp);
			parser_node = parser_node->next;				
		}
		free(parser_node);
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
	fork_router(init, envp);
/* 	while (strings_env[++i])
		ft_printf("%s", strings_env[i]); */
	ft_free_smatrix(strings_env);
}
