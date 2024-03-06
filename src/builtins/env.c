/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:21:20 by patatoss          #+#    #+#             */
/*   Updated: 2024/03/06 09:35:24 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env(t_mshell *init)
{
	t_env	*env_head;

	env_head = init->env_table;
	while (init->env_table)
	{
		if (init->env_table->visibility == 0 && init->env_table->content)
			printf("%s=%s\n", init->env_table->var, init->env_table->content);
		init->env_table = init->env_table->next;
	}
	init->env_table = env_head;
	exit(EXIT_SUCCESS);
}
