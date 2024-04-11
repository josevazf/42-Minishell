/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:21:20 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/11 13:50:38 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env(t_mshell *init, t_parser *par_node)
{
	t_env	*env_head;

	if (par_node->cmd_exec[1] && par_node->cmd_exec[1][0] == '-')
		write(par_node->output, "minishell: env does not accept any options\n", 43);
	else
	{
		env_head = init->env_table;
		while (init->env_table)
		{
			if (init->env_table->visibility == 0 && init->env_table->content)
				printf("%s=%s\n", init->env_table->var, init->env_table->content);
			init->env_table = init->env_table->next;
		}
		init->env_table = env_head;
	}
	delete_lists(init);
	exit(EXIT_SUCCESS);
}
