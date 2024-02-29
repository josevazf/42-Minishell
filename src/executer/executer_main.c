/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:26:40 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/02/29 17:59:04 by jrocha-v         ###   ########.fr       */
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

void	executer_fork_router(t_mshell *init, char ***env, int *exit_code, int i)
{
	int			**pipe_fds;
	int			*child_pids;
	t_parser	*parser_node;

	get_pipes(init);
	pipe_fds = NULL;
	if (init->nbr_pipes == 0)
		process_single_cmd(init, env, exit_code);
	else if (init->parser->cmd_exec != NULL)
	{
		pipe_fds = process_pipes(init, pipe_fds);
		parser_node = init->parser;
		child_pids = (int *)malloc(sizeof(int) * (init->nbr_pipes + 1));
		malloc_error(child_pids);
		while (i++ <= init->nbr_pipes)
		{
			child_pids[i - 1] = fork();
			fork_error(child_pids[i - 1]);
			if (child_pids[i - 1] == 0)
			{
				if (child_pids != NULL)
					free(child_pids);
				init->cmd_index = i;
				process_child(init, pipe_fds, parser_node, env, exit_code);
			}
			parser_node = parser_node->next;
		}
		process_parent(init, pipe_fds, child_pids, exit_code);
		if (pipe_fds != NULL)
			ft_free_imatrix(pipe_fds);
	}
}

void	executer_main(t_mshell *init, char ***envp_copy, int *exit_code)
{
	if (init->stop_redirs)
	{
		*exit_code = 2;
		return ;
	}
	signal(SIGINT, sighandler_fork);
	signal(SIGQUIT, sighandler_fork);
	executer_fork_router(init, envp_copy, exit_code, 0);
	dup2(init->og_stdin, STDIN_FILENO);
	dup2(init->og_stdout, STDOUT_FILENO);
}
