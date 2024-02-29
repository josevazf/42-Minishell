/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_redirs_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:33:28 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/02/29 11:45:30 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	check_red_error(char *redir_syntax)
{
	if (!ft_strncmp(redir_syntax, "<", 1) || !ft_strncmp(redir_syntax, ">", 1))
	{
		printf("\nasneira\n");
		return (1);
	}
	return (0);
}

int	process_file(t_mshell *init, char *file_name, int file_type)
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
