/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:21:20 by patatoss          #+#    #+#             */
/*   Updated: 2024/02/15 11:54:27 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env(t_mshell *init)
{
	t_env	*env_head;

	env_head = init->env_table;
	while (init->env_table)
	{
		if (init->env_table->visibility == 0)
		{
			ft_printf("%s", init->env_table->var);
			if (init->env_table->content)
				ft_printf("=%s", init->env_table->content);
			ft_printf("\n");
		}
		init->env_table = init->env_table->next;
	}
	init->env_table = env_head;
	exit(EXIT_SUCCESS);
}
