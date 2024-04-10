/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:08:28 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/10 22:32:16 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Deal with file/directory not found */
int	file_error(char *file_name)
{
	printf("minishell: %s: No such file or directory", file_name);
	exit(EXIT_FAILURE);
}

/* Deal with error definning redirs tokens */
int	redirs_error(t_mshell *init, t_parser *parser_node, int *exit_code)
{
	if (*exit_code == 130)
		return (130);
	if (parser_node->token_err)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (2);
	}
	else if (parser_node->file_nf)
		return (1);
	else
	{
		dup2(init->og_stdin, STDIN_FILENO);
		dup2(init->og_stdout, STDOUT_FILENO);
		return (0);
	}
}

/* Deal with file descriptor failure */
int	fd_error(int fd)
{
	if (fd < 0)
		ft_error("minishell: file error", ERROR);
	return (EXIT_FAILURE);
}

void	safe_close(int fd)
{
	if (fd < 0)
		return ;
	close(fd);
}
