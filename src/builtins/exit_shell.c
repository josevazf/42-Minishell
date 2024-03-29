/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:21:50 by tiaferna          #+#    #+#             */
/*   Updated: 2024/03/29 23:11:28 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_exit_args(char **exit_in, int *exit_code, int i, int sign)
{
	if (exit_in[2] == NULL)
	{
		while (exit_in[1][++i])
		{
			if (exit_in[1][i] == '+')
				i++;
			if (exit_in[1][i] == '-')
			{
				sign = sign * -1;
				i++;
			}
			if ((!ft_isdigit(exit_in[1][i]) && exit_in[1][i]) || ((sign == 1 \
				&& ft_atoll(exit_in[1]) > LLONG_MAX) || (sign == -1 \
				&& ft_atoll(exit_in[1]) > (unsigned long long)(LLONG_MAX) + 1)))
			{
				*exit_code = 2;
				return (TRUE_EXIT);
			}
		}
		*exit_code = ((int)(ft_atoll(exit_in[1]) * sign) % 256 + 256) % 256;
		printf("exit\n");
	}
	return (*exit_code);
}

int	exit_arguments(char *input, int exit_code)
{
	char	**exit_in;

	if (input)
	{
		exit_in = ft_split(input, ' ');
		if (exit_in[1] == NULL && !ft_iswhitespace(input[0]))
		{
			printf("exit\n");
			exit_code = exit_code - 100;
		}
		else if (check_exit_args(exit_in, &exit_code, -1, 1) == TRUE_EXIT)
			printf("exit\nminishell: exit: %s: numeric argument required\n", \
				exit_in[1]);
		else if (exit_in[2] != NULL && exit_code != 1)
		{
			printf("exit\nminishell: exit: too many arguments\n");
			add_history(input);
			exit_code = ARGS_EXIT;
		}
		ft_free_smatrix(exit_in);
	}
	else
		printf("exit\n");
	return (exit_code);
}

int	process_exit(char *input, int *exit_code)
{
	if (input == NULL || !ft_strncmp(input, "exit", 4))
	{
		*exit_code = exit_arguments(input, *exit_code);
		if ((*exit_code != TRUE_EXIT || input == NULL) \
			&& *exit_code != ARGS_EXIT)
			return (0);
		else if (*exit_code == ARGS_EXIT)
			*exit_code = 1;
		return (1);
	}
	return (2);
}
