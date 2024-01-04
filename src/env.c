/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patatoss <patatoss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:21:20 by patatoss          #+#    #+#             */
/*   Updated: 2024/01/04 18:59:11 by patatoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	env(t_mshell *init)
{
	t_env	*env_head;

	env_head = init->env_table;
	while (init->env_table)
	{
		ft_printf("%s", init->env_table->var);
		if (init->env_table->content)
			ft_printf("=%s", init->env_table->content);
		ft_printf("\n");
		init->env_table = init->env_table->next;
	}
	init->env_table = env_head;
}
