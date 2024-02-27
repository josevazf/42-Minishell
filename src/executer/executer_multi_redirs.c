/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_multi_redirs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:08:06 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/02/26 16:05:54 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	multi_check_input(t_mshell *init, t_parser *node, int i)
{
	char	**red_full;

	node->input_t = NO_RED;
	if (node->redirs)
	{	
		red_full = ft_split(node->redirs, '\t');
		if (red_full[1] == NULL)
		{
			node->token_err = true;
			node->input_t = INVALID;
			ft_free_smatrix(red_full);
			return ;
		}
		while (red_full[++i])
		{
			if (!ft_strncmp(red_full[i], "<<", 2))
				node->input_t = IN_HD;
			else if (!ft_strncmp(red_full[i], "<", 1))
				node->input_t = IN_FILE;				
		}
		ft_free_smatrix(red_full);
	}
	if (node->input_t != IN_HD && node->input_t != IN_FILE && init->cmd_index != 1)
		node->input_t = IO_PIPE;
}

void	multi_check_output(t_mshell *init, t_parser *node, int i)
{
	char	**red_full;
	
	(void)init;
	node->output_t = NO_RED;
	if (node->redirs)
	{	
		red_full = ft_split(node->redirs, '\t');
		if (red_full[1] == NULL)
		{
			node->token_err = true;
			node->output_t = INVALID;
			ft_free_smatrix(red_full);
			return ;
		}
		while (red_full[++i])
		{
			if (!ft_strncmp(red_full[i], ">>", 2))
				node->output_t = OUT_FILE_APND;
			else if (!ft_strncmp(red_full[i], ">", 1))
				node->output_t = OUT_FILE_OWR;
		}
		ft_free_smatrix(red_full);
	}
	if (node->next && node->output_t != OUT_FILE_APND && node->output_t != OUT_FILE_OWR)
		node->output_t = IO_PIPE;
}

void	multi_redir_input(t_mshell *init, t_parser *node, int **pipe_fds)
{
	int		i;
	char	**red_full;

	i = -1;
	if (node->input_t == IN_HD || node->input_t == IN_FILE)
	{	
		red_full = ft_split(node->redirs, '\t');
		while (red_full[++i])
		{
			if (!ft_strncmp(red_full[i], "<<", 2))
				node->input = process_here_doc(init, red_full[i + 1]);	
			else if (!ft_strncmp(red_full[i], "<", 1))
				node->input = single_process_file(init, red_full[i + 1], IN_FILE);
		}
		if (node->input == -1)
			node->file_nf = true;
		ft_free_smatrix(red_full);
	}
	else if (node->input_t == IO_PIPE)
		node->input = pipe_fds[init->cmd_index - 2][0];
	if (node->input_t != NO_RED)
		dup2(node->input, STDIN_FILENO);		
}

void	multi_redir_output(t_mshell *init, t_parser *node, int **pipe_fds)
{
	int		i;
	char	**red_full;

	i = -1;
	if (node->output_t == OUT_FILE_APND || node->output_t == OUT_FILE_OWR)
	{	
		red_full = ft_split(node->redirs, '\t');
		while (red_full[++i])
		{
			if (!ft_strncmp(red_full[i], ">>", 2))
				node->output = single_process_file(init, red_full[i + 1], OUT_FILE_APND);
			else if (!ft_strncmp(red_full[i], ">", 1))
				node->output = single_process_file(init, red_full[i + 1], OUT_FILE_OWR);
		}
		if (node->output == -1)
			node->file_nf = true;
		ft_free_smatrix(red_full);
	}
	else if (node->output_t == IO_PIPE)
		node->output = pipe_fds[init->cmd_index - 1][1];
	if (node->output_t != NO_RED)
		dup2(node->output, STDOUT_FILENO);
}

void	multi_redirs_router(t_mshell *init, t_parser *node, int **pipe_fds)
{
	multi_check_input(init, node, -1);
	multi_check_output(init, node, -1);
	multi_redir_input(init, node, pipe_fds);
	multi_redir_output(init, node, pipe_fds);
	close_redirs_pipes(init, pipe_fds, node);
}
