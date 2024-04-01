/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:05:37 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/01 18:47:12 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Get here_doc input and write to pipe */
void	write_here_doc(t_mshell *init, char *eof, int *pipe_fd, int *exit_code)
{
	char	*input;

	signal(SIGINT, sigint_hdhandler);
	signal(SIGQUIT, SIG_IGN);
	input = readline("> ");
	if (!input)
	{
		printf("minishell: warning: here-document delimited by end-of-file \
(wanted `%s')\n", init->eof);
		close(pipe_fd[1]);
		delete_lists(init);
		exit(EXIT_FAILURE);
	}
	input = ft_strupdate(input, "\n");
	if (ft_strlen(input) == (ft_strlen(eof) + 1) && \
		ft_strncmp(input, eof, ft_strlen(eof)) == 0)
	{
		free_hd_vars(init->redirs, input, pipe_fd[1]);
		delete_lists(init);
		exit(EXIT_SUCCESS);
	}
	if (init->expand_heredoc == true)
		heredoc_expander(init, &input, exit_code);
	write(pipe_fd[1], input, ft_strlen(input));
	free(input);
}

/* Process here_doc */
int	process_here_doc(t_mshell *init, char *eof, int *exit_code, int export)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;

	pipe_error(pipe(pipe_fd));
	fork_error(pid = fork());
	if (pid == 0)
	{
		free_hd_vars(*init->envp_copy, NULL, pipe_fd[0]);
		while (1)
			write_here_doc(init, eof, pipe_fd, exit_code);
	}
	else
	{
		close(pipe_fd[1]);
		export = dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		waitpid(pid, &status, 0);
		if (g_signo == 130)
		{
			*exit_code = 130;
			return (-1);
		}
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

void	exec_executable(t_mshell *init, t_parser *parser_node)
{
	char	*file_err;

	(void)init;
	if (open(parser_node->cmd_exec[0], O_WRONLY | O_RDONLY) == -1 && \
		errno != 26)
	{
		file_err = NULL;
		file_err = strerror(errno);
		printf("minishell: %s: %s\n", parser_node->cmd_exec[0], file_err);
		if (errno >= 13)
			exit(126);
		else
			exit(127);
	}
	else if (access(parser_node->cmd_exec[0], X_OK) != 0)
	{
		file_err = strerror(errno);
		printf("minishell: %s: %s\n", parser_node->cmd_exec[0], file_err);
		if (errno == 13)
			exit(126);
		else
			exit(127);
	}
	execve(parser_node->path_exec, parser_node->cmd_exec, NULL);
	exit(EXIT_SUCCESS);
}

void	executer_cmd_router(t_mshell *init, t_parser *parser_node,
			char ***envp, int *exit_code)
{
	if (!ft_strcmp(parser_node->cmd_exec[0], "echo"))
	{
		ft_free_smatrix(*envp);
		echo(parser_node, 2, 1, init);
	}
	else if (!ft_strcmp(parser_node->cmd_exec[0], "cd"))
		cd(init, parser_node, exit_code, envp);
	else if (!ft_strcmp(parser_node->cmd_exec[0], "pwd"))
	{
		ft_free_smatrix(*envp);
		pwd(init, parser_node);
	}
	else if (!ft_strcmp(parser_node->cmd_exec[0], "export"))
	{
		export(init, envp, exit_code);
		exit(EXIT_SUCCESS);
	}
	else if (!ft_strcmp(parser_node->cmd_exec[0], "unset"))
		unset(init, envp);
	else if (!ft_strcmp(parser_node->cmd_exec[0], "env"))
		pre_env_exec(init, parser_node, envp);
	else if (!ft_strncmp(parser_node->cmd_exec[0], "./", 2))
		exec_executable(init, parser_node);
	else
		execve(parser_node->path_exec, parser_node->cmd_exec, *envp);
}
