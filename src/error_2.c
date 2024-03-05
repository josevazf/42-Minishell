/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:08:28 by tiago             #+#    #+#             */
/*   Updated: 2024/03/05 00:09:28 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	file_error(char *file_name)
{
	printf("minishell: %s: No such file or directory", file_name);
	exit(EXIT_FAILURE);
}

int	redirs_error(t_parser *parser_node)
{
	if (parser_node->token_err)
	{
		ft_printf("minishell: syntax error near unexpected token `newline'\n");
		return (2);
	}
	else if (parser_node->file_nf)
		return (1);
	else
		return (0);
}

/* Deal with file descriptor failure */
int	fd_error(int fd)
{
	if (fd < 0)
		ft_error("minishell: file error", ERROR);
	return (EXIT_FAILURE);
}
