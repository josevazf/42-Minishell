/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_single_redirs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:56:54 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/02/27 17:41:37 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	single_process_file(t_mshell *init, char *file_name, int file_type)
{
	int		file_fd;
	int		export;
	char	*file_err;

	(void)init;
	if (file_type == IN_FILE)
		file_fd = open(file_name, O_RDONLY);
	if (file_type == OUT_FOWR)
		file_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_type == OUT_FAPND)
		file_fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file_fd == -1)
	{
		file_err = strerror(errno);
		printf("minishell: %s: %s\n", file_name, file_err);
		return (-1);
	}
	if (file_type == IN_FILE)
		export = dup2(file_fd, STDIN_FILENO);
	if (file_type != IN_FILE)
		export = dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	return (export);
}

void	single_redirs_router(t_mshell *init, t_parser *node)
{
	int		i;
	char	**redirs;

	i = -1;
	redirs = ft_split(node->redirs, '\t');
	if (redirs[1] == NULL || redirs[3] == NULL)
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
			node->input = single_process_file(init, redirs[i + 1], IN_FILE);
		else if (!ft_strncmp(redirs[i], ">>", 2))
			node->output = single_process_file(init, redirs[i + 1], OUT_FAPND);
		else if (!ft_strncmp(redirs[i], ">", 1))
			node->output = single_process_file(init, redirs[i + 1], OUT_FOWR);
		if (node->output == -1 || node->input == -1)
			node->file_nf = true;
	}
	ft_free_smatrix(redirs);
}
