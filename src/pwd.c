/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 08:04:58 by tiaferna          #+#    #+#             */
/*   Updated: 2023/12/29 09:42:26 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(t_mshell *init)
{
	t_env *env_head;

	env_head = init->env_table;
	while (init->env_table)
	{
		if (ft_strcmp("PWD", init->env_table->var) == 0)
		{
			write(1, init->env_table->content, ft_strlen(init->env_table->content));
			write(1, "\n", 1);
			return ;
		}
		init->env_table = init->env_table->next;
	}
	init->env_table = env_head;
	return ;
}
