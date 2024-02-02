/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:41:51 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/02/01 18:51:46 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int redirs_error(void)
{
	ft_printf("minishell: syntax error near unexpected token `newline'");
	exit (ERROR);
}

/* Deal with malloc failure */
int	malloc_error(void *input)
{
	if (input == NULL)
		ft_error("minishell: malloc failed", ERROR);
	return (SUCCESS);
}

/* Deal with file descriptor failure */
int	fd_error(int fd)
{
	if (fd == -1)
		ft_error("minishell: file error", ERROR);
	return (SUCCESS);
}

/* Deal with bad arguments */
int	args_error(void)
{
	ft_printf("minishell usage: ./minishell\n");
	exit (ERROR);
}

/* Deal with unclosed quotes */
int	quotes_error(void)
{
	ft_printf("minishell: unclosed quotes\n");
	exit (ERROR);
}