/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:41:51 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/03/05 00:10:00 by tiago            ###   ########.fr       */
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

/* Deal with bad arguments */
int	args_error(void)
{
	ft_printf("minishell usage: ./minishell\n");
	exit(EXIT_FAILURE);
}

/* Deal with unclosed quotes */
int	quotes_error(void)
{
	ft_printf("minishell: unclosed quotes\n");
	exit(EXIT_FAILURE);
}
