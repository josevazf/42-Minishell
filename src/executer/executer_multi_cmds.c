/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_multi_cmds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:40:54 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/01 21:15:41 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	multi_cmd_isdir(t_mshell *init, char *cmd)
{
	char	*file_err;

	dup2(init->og_stdin, STDIN_FILENO);
	dup2(init->og_stdout, STDOUT_FILENO);
	file_err = strerror(errno);
	printf("minishell: %s: %s\n", cmd, file_err);
	if (errno >= 13)
		return (126);
	else
		return (127);
}

int	multi_cmd_notfound(t_mshell *init, t_parser *parser_node)
{
	char	*error_msg;

	error_msg = NULL;
	dup2(init->og_stdin, STDIN_FILENO);
	dup2(init->og_stdout, STDOUT_FILENO);
	if ((open(parser_node->cmd_exec[0], O_WRONLY) == -1 && \
		parser_node->cmd_exec[0] \
		[ft_strlen(parser_node->cmd_exec[0]) - 1] == '/') || \
		(access(parser_node->cmd_exec[0], F_OK) == -1 && \
		check_forwardslash(parser_node->cmd_exec[0]) == 0))
	{
		error_msg = strerror(errno);
		printf("minishell: %s: %s\n", parser_node->cmd_exec[0], error_msg);
		if (errno >= 13)
			return (126);
		else
			return (127);
	}
	error_msg = ft_strjoin(parser_node->cmd_exec[0], ": command not found\n");
	printf("%s", error_msg);
	free(error_msg);
	return (127);
}

void	process_pipes(t_mshell *init)
{
	int	i;

	i = -1;
	if (init->nbr_pipes == 0)
		return ;
	init->pipe_fds = (int **)malloc(sizeof(int *) * (init->nbr_pipes + 1));
	malloc_error(init->pipe_fds);
	init->closed_pipes = (int **)malloc(sizeof(int *) * (init->nbr_pipes + 1));
	malloc_error(init->closed_pipes);
	init->pipe_fds[init->nbr_pipes] = NULL;
	init->closed_pipes[init->nbr_pipes] = NULL;
	while (++i < init->nbr_pipes)
	{
		init->pipe_fds[i] = (int *)malloc(sizeof(int) * 2);
		malloc_error(init->pipe_fds[i]);
		init->closed_pipes[i] = (int *)malloc(sizeof(int) * 2);
		malloc_error(init->closed_pipes[i]);
		init->closed_pipes[i][0] = 0;
		init->closed_pipes[i][1] = 0;
		if (pipe(init->pipe_fds[i]) == -1)
			ft_error("minishell: failed creating pipe", ERROR);
	}
}

void	process_child(t_mshell *init, t_parser *parser_node, char ***envp,
			int *exit_code)
{
	close_child_pipes(init);
	multi_redirs_router(init, parser_node, exit_code);
	if (parser_node->token_err || parser_node->file_nf)
	{
		*exit_code = redirs_error(parser_node, exit_code);
		free_all(init, envp);
		exit(*exit_code);
	}
	else if (!parser_node->path_exec && parser_node->redirs)
	{
		*exit_code = 1;
		free_all(init, envp);
		return ;
	}
	else if (!ft_strcmp(parser_node->path_exec, "notfound"))
	{
		if (access(parser_node->cmd_exec[0], X_OK) == -1 && \
				(parser_node->cmd_exec[0] \
				[ft_strlen(parser_node->cmd_exec[0]) - 1] == '/' || \
				parser_node->cmd_exec[0][0] == '/'))
			*exit_code = multi_cmd_isdir(init, parser_node->cmd_exec[0]);
		else
			*exit_code = multi_cmd_notfound(init, parser_node);
		free_all(init, envp);
		exit(*exit_code);
	}
	if (parser_node->cmd_exec != NULL)
		executer_cmd_router(init, parser_node, envp, exit_code);
}

void	process_parent(t_mshell *init, int *exit_code)
{
	int	i;
	int	status;

	i = -1;
	close_parent_pipes(init);
	while (++i < (init->nbr_pipes + 1))
	{
		if (waitpid(init->child_pids[i], &status, 0) != -1)
			get_exit_code(status, exit_code);
	}
}
