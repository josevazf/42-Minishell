/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:25:18 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/03/05 00:11:26 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_prompt_and_get_input(char **envp, char **input, char **line)
{
	*line = prompt_line(envp);
	*input = readline(*line);
	free(*line);
}

void	parse_and_execute(t_mshell *init, char ***envp_copy, int *exit_code)
{
	if (ft_strlen(init->in) > 0)
	{
		parser_main(init, envp_copy, NULL, NULL);
		executer_main(init, envp_copy, exit_code);
	}
	delete_lists(init);
}

void	free_and_clear(char **envp)
{
	ft_free_smatrix(envp);
	rl_clear_history();
}

int	check_whitespace(char *input)
{
	int	i;

	i = 0;
	if (input == NULL)
		return (EXIT_SUCCESS);
	while (input[i] && input[i] != '\0')
	{
		if (!ft_iswhitespace(input[i]) || input[i] == '\0')
			return (EXIT_SUCCESS);
		i++;
	}
	free(input);
	return (EXIT_FAILURE);
}
