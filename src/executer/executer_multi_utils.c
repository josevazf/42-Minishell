/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_multi_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:47:40 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/03/06 18:34:28 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_parent_pipes(t_mshell *init)
{
	int	i;

	(void)init;
	i = 0;
	while (init->pipe_fds[i])
	{
		if (close(init->pipe_fds[i][0]) > 0)
			ft_error("minishell: error closing parent fd 0", ERROR);
		if (close(init->pipe_fds[i][1]) > 0)
			ft_error("minishell: error closing parent fd 1", ERROR);
		i++;
	}
}

void	close_pipes(t_mshell *init)
{
	int	i;

	i = 0;
	if (!init->pipe_fds)
		return ;
	while (init->pipe_fds[i])
	{
		if (i != init->cmd_index - 2)
		{
			if (close(init->pipe_fds[i][0]) == -1)
				ft_error("minishell: error closing pipe", ERROR);
		}
		if (i != init->cmd_index - 1)
		{
			if (close(init->pipe_fds[i][1]) == -1)
				ft_error("minishell: error closing pipe", ERROR);
		}
		i++;
	}
}

void	close_redirs_pipes(t_mshell *init, t_parser *node)
{
	if (!init->pipe_fds)
		return ;
	if (init->cmd_index > 1)
	{
		if (close(init->pipe_fds[init->cmd_index - 2][0]) == -1)
			ft_error("minishell: error closing pipe", ERROR);
	}
	if (node->next)
	{
		if (close(init->pipe_fds[init->cmd_index - 1][1]) == -1)
			ft_error("minishell: error closing pipe", ERROR);
	}
}
