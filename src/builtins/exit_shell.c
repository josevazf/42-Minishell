/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:21:50 by tiaferna          #+#    #+#             */
/*   Updated: 2024/03/29 12:31:48 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_exit_args(char **exit_in, int *exit_code)
{
	int	i;
	int sign;

	i = -1;
	sign = 1;
	while (exit_in[1][++i])
	{
		if (exit_in[1][i] == '+')
			i++;
		if (exit_in[1][i] == '-')
		{
			sign = sign * -1;
			i++;
		}
		if ((!ft_isdigit(exit_in[1][i]) && exit_in[1][i]) \
		|| (ft_atoll(exit_in[1]) * sign) > LONG_MAX || (ft_atoll(exit_in[1]) * sign) < LONG_MIN)
		{
			*exit_code = 2;
			return (ERROR);
		}
	}
	*exit_code = (ft_atoll(exit_in[1]) % 256 + 256) % 256;
	printf("exit\n");
	return (*exit_code);
}

void	free_exit_args(char *input, char **exit_in)
{
	free(input);
	ft_free_smatrix(exit_in);
}

int	exit_arguments(char *input, int exit_code)
{
	char	**exit_in;

	if (input)
	{
		input = ft_strupdate(input, " ");
		exit_in = ft_split(input, ' ');
		if (exit_in[1] == NULL && !ft_iswhitespace(input[0]))
		{
			printf("exit\n");
			exit_code = exit_code - 100;
		}
		else if (check_exit_args(exit_in, &exit_code) == ERROR)
			printf("exit\nminishell: exit: %s: numeric argument required\n", \
				exit_in[1]);
		else if (exit_in[2] != NULL)
		{
			printf("minishell: exit: too many arguments\n");
			add_history(input);
			exit_code = 1;
		}
		free_exit_args(input, exit_in);
	}
	else
		printf("exit\n");
	return (exit_code);
}
