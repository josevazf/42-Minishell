/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:44:46 by tiago             #+#    #+#             */
/*   Updated: 2024/02/29 16:32:44 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env_node(t_env *env_node, t_mshell *init)
{
	if (init)
		init->env_table = init->env_table->next;
	free(env_node->var);
	free(env_node->content);
	free(env_node);
}

void	unset(t_mshell *init, char **envp_copy)
{
	t_env	*env_node;
	t_env	*temp;
	int		i;
	
	if (!init->parser->cmd_exec[1])
		return ;
	i = 1;
	while (init->parser->cmd_exec[i])
	{
		env_node = init->env_table;
		if (ft_strcmp(env_node->var, init->parser->cmd_exec[i]) == 0) 
			free_env_node(env_node, init);
		else
		{
			while (env_node->next)
			{
				if (ft_strcmp(env_node->next->var, init->parser->cmd_exec[i]) == 0)
				{
					temp = env_node->next;
					env_node->next = env_node->next->next;
					free_env_node(temp, init);
					break ;
				}
				env_node = env_node->next;
			}
		}
		i++;
	}
	envp_copy = update_envp_copy(init, &envp_copy);
}
