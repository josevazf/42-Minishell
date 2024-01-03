/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patatoss <patatoss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:22:25 by patatoss          #+#    #+#             */
/*   Updated: 2024/01/03 22:35:58 by patatoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	save_in_stash(t_env *node, t_env *stash)
{
	t_env *stash_node;

	stash_node = stash;
	if (!stash_node->var)
		stash_node->var = ft_strdup(node->var);
	else
	{
		while(stash_node->next)
			stash_node = stash_node->next;
		stash_node->next = (t_env *)malloc(sizeof(t_env));
		stash_node = stash_node->next;
		stash_node->var = NULL;
		stash_node->content = NULL;
		stash_node->next = NULL;
		stash_node->var = ft_strdup(node->var);
	}
}

int	check_stash(t_env *node, t_env *stash)
{
	t_env *stash_node;

	stash_node = stash;
	while (stash_node)
	{
		// ft_printf("node->var = %s, stash_node->var = %s\n", node->var, stash_node->var);
		if (ft_strcmp(node->var, stash_node->var) == 0)
			return (0);
		stash_node = stash_node->next;
	}
	return (1);
}

void	export(t_mshell *init)
{
	t_env	*env_node;
	t_env	*to_print;
	t_env	*count;
	t_env	*stash;
	
	stash = (t_env *)malloc(sizeof(t_env));
	stash->var = NULL;
	stash->content = NULL;
	stash->next = NULL;
	env_node = init->env_table;
	count = init->env_table;

	while (count)
	{
		to_print = env_node;
		while (env_node)
		{
			if (ft_strcmp(to_print->var, env_node->var) < 0)
				to_print = env_node;
			env_node = env_node->next;
		}
		env_node = init->env_table;
		while (env_node)
		{
			while (env_node && stash->var && check_stash(env_node, stash) == 0)
				env_node = env_node->next;
			if (!env_node)
				break ;
			if (ft_strcmp(to_print->var, env_node->var) > 0)
				to_print = env_node;
			env_node = env_node->next;
		}
		ft_printf("declare -x %s=%s\n", to_print->var, to_print->content);
		save_in_stash(to_print, stash);
		env_node = init->env_table;
		count = count->next;
	}
}
