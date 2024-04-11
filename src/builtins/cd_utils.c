/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:00:47 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/11 12:48:57 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_oldpwd(t_mshell *init)
{
	t_env	*env_node;

	env_node = init->env_table;
	while (env_node)
	{
		if (ft_strcmp(env_node->var, "OLDPWD") == 0)
			if (env_node->content)
				return (env_node->content);
		env_node = env_node->next;
	}
	return (NULL);
}
