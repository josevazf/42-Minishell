/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:56:54 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/02/27 17:38:38 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_file(t_mshell *init, char *file_name, int file_type)
{
	int	file_fd;
	int	export;
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

void	redirs_router(t_mshell *init, char *redirs)
{
	int		i;
	char	**red_full;
	
	i = -1;
	red_full = ft_split(redirs, '\t');
	if (red_full[1] == NULL)
	{
		ft_free_smatrix(red_full);
		redirs_error();
		return ;
	}
	while (red_full[++i])
	{
		if (!ft_strncmp(red_full[i], "<<", 2))
			init->red_input = process_here_doc(init, red_full[i + 1]);	
		else if (!ft_strncmp(red_full[i], "<", 1))
			init->red_input = process_file(init, red_full[i + 1], IN_FILE);
		else if (!ft_strncmp(red_full[i], ">>", 2))
			init->red_output = process_file(init, red_full[i + 1], OUT_FAPND);
		else if (!ft_strncmp(red_full[i], ">", 1))
			init->red_output = process_file(init, red_full[i + 1], OUT_FOWR);
		if (init->red_output == -1 || init->red_input == -1)
			init->stop_redirs = true;
	}
	ft_free_smatrix(red_full);
}
