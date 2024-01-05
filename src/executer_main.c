/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:26:40 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/05 11:57:02 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"

char	**convert_env(t_mshell *init)
{
	char	**strings_env;
	char	*temp_line;
	
	while (init->env_table)
	{
		temp_line = ft_strjoin(init->env_table->var, "=");
		temp_line = ft_strjoin(temp_line, init->env_table->content);
		temp_line = ft_strjoin(temp_line, "\n\t");
		init->env_table = init->env_table->next;
	}
	strings_env = ft_split(temp_line, '\t');
	free(temp_line);
	return (strings_env);
}

void	executer_main(t_mshell *init)
{
	
}