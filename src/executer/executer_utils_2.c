/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:20:30 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/01 20:07:06 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	hd_delete_lists(t_mshell *init)
{
	init->set_var = false;
	init->nbr_pipes = 0;
	init->cmd_index = 0;
	init->og_stdin = 0;
	init->og_stdout = 0;
	init->red_input = 0;
	init->red_output = 0;
	init->expand_heredoc = false;
	init->stop_exec = false;
}

void	free_all(t_mshell *init, char ***envp)
{
	delete_lists(init);
	ft_free_smatrix(*envp);
}

void	free_hd_vars(char **redirs, char *input, int pipe_fd)
{
	ft_free_smatrix(redirs);
	if (input)
		free(input);
	close(pipe_fd);
}

void	free_exec_helper(t_mshell *init, t_parser *parser_node, char ***envp,
			char *file_err)
{
	printf("minishell: %s: %s\n", parser_node->cmd_exec[0], file_err);
	free_all(init, envp);
}

void	pre_env_exec(t_mshell *init, t_parser *parser_node, char ***envp)
{
	ft_free_smatrix(*envp);
	if (!parser_node->cmd_exec[1])
		env(init);
	printf("env: '%s': No such file or directory\n",
		parser_node->cmd_exec[1]);
	exit(127);
}
