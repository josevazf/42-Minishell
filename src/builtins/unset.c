/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:44:46 by tiago             #+#    #+#             */
/*   Updated: 2024/02/13 12:18:57 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env_node(t_env *env_node)
{
	free(env_node->var);
	free(env_node->content);
	free(env_node);
}

void	unset(t_mshell *init)
{
	t_env	*env_node;
	t_env	*temp;

	env_node = init->env_table;
	if (ft_strcmp(env_node->var, init->lexer->next->str) == 0)
	{
		init->env_table = init->env_table->next;
		free_env_node(env_node);
	}
	else
	{
		while (env_node->next)
		{
			if (ft_strcmp(env_node->next->var, init->lexer->next->str) == 0)
			{
				temp = env_node->next;
				env_node->next = env_node->next->next;
				free_env_node(temp);
			}
			env_node = env_node->next;
		}
	}
	exit(EXIT_SUCCESS);
}
