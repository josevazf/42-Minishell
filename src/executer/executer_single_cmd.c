/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_single_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:35:49 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/02/29 11:43:01 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	single_cmd_notfound(t_mshell *init)
{
	char	*error_msg;

	error_msg = NULL;
	dup2(init->og_stdin, STDIN_FILENO);
	dup2(init->og_stdout, STDOUT_FILENO);
	error_msg = ft_strjoin(init->parser->cmd_exec[0], ": command not found\n");
	printf("%s", error_msg);
	free(error_msg);
	return (127);
}

/* Fork single command */
void	fork_single_cmd(t_mshell *init, t_parser *parser_node, char **envp, \
													int *exit_code)
{
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid == -1)
		ft_error("minishell: failed creating fork", ERROR);
	if (pid == 0 && parser_node->cmd_exec != NULL)
	{
		executer_cmd_router(init, parser_node, envp, exit_code);
		close(pid);
	}
	else
	{
		if (waitpid(pid, &status, 0) != -1)
		{
			close(pid);
			get_exit_code(status, exit_code);
		}
		else
			ft_error("waitpid() failed", EXIT_FAILURE);
	}
}

/* Process single command */
void	process_single_cmd(t_mshell *init, char **envp, int *exit_code)
{
	if (init->parser->redirs)
		single_redirs_router(init, init->parser);
	if (init->parser->token_err)
	{
		*exit_code = redirs_error();
		return ;
	}
	else if (!init->parser->path_exec && init->parser->redirs)
	{
		*exit_code = 1;
		return ;
	}
	else if (!ft_strcmp(init->parser->path_exec, "notfound"))
	{
		*exit_code = single_cmd_notfound(init);
		return ;
	}
	if (!ft_strncmp(init->parser->cmd_exec[0], "cd", 2))
		cd(init, init->parser, exit_code, envp);
	else if (!ft_strncmp(init->parser->cmd_exec[0], "unset", 5))
		unset(init, envp);
	else if (!ft_strncmp(init->parser->cmd_exec[0], "export", 6))
		export(init, envp, exit_code);
	else if (init->parser->cmd_exec != NULL)
		fork_single_cmd(init, init->parser, envp, exit_code);
}

void	single_redirs_router(t_mshell *init, t_parser *node)
{
	int		i;
	char	**redirs;

	i = -1;
	redirs = ft_split(node->redirs, '\t');
	if (redirs[1] == NULL || redirs[3] == NULL || check_red_error(redirs[1]))
	{
		node->token_err = true;
		ft_free_smatrix(redirs);
		return ;
	}
	while (redirs[++i])
	{
		if (!ft_strncmp(redirs[i], "<<", 2))
			node->input = process_here_doc(init, redirs[i + 1]);
		else if (!ft_strncmp(redirs[i], "<", 1))
			node->input = process_file(init, redirs[i + 1], IN_FILE);
		else if (!ft_strncmp(redirs[i], ">>", 2))
			node->output = process_file(init, redirs[i + 1], OUT_FAPND);
		else if (!ft_strncmp(redirs[i], ">", 1))
			node->output = process_file(init, redirs[i + 1], OUT_FOWR);
		if (node->output == -1 || node->input == -1)
			node->file_nf = true;
	}
	ft_free_smatrix(redirs);
}
