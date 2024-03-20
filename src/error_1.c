/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:41:51 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/03/20 17:42:28 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Deal with malloc failure */
int	malloc_error(void *input)
{
	if (input == NULL)
		ft_error("minishell: malloc failed", ERROR);
	return (EXIT_FAILURE);
}

/* Deal with fork failure */
int	fork_error(int pid)
{
	if (pid < 0)
		ft_error("minishell: fork error", ERROR);
	return (EXIT_FAILURE);
}

/* Deal with pipe failure */
int	pipe_error(int pid)
{
	if (pid < 0)
		ft_error("minishell: pipe error", ERROR);
	return (EXIT_FAILURE);
}

/* Deal with bad arguments */
int	args_error(void)
{
	printf("minishell usage: ./minishell\n");
	exit(EXIT_FAILURE);
}

/* Deal with unclosed quotes */
int	quotes_error(void)
{
	printf("minishell: unclosed quotes\n");
	exit(EXIT_FAILURE);
}
