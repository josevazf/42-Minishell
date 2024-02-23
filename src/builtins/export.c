/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:22:25 by patatoss          #+#    #+#             */
/*   Updated: 2024/02/21 12:55:56 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int var_exists(t_mshell *init, t_env *env_node, char **envp_copy)
{
	char **export_split;

	export_split = ft_split(init->parser->cmd_exec[1], '=');
	while (env_node)
	{
		if (ft_strcmp(env_node->var, export_split[0]) == 0)
		{
			env_node->visibility = 0;
			if (export_split[1])
			{
				if (env_node->content)
					free(env_node->content);
				env_node->content = ft_strdup(export_split[1]);
			}
			envp_copy = update_envp_copy(init, envp_copy);
			ft_free_smatrix(export_split);
			return (0);
		}
		env_node = env_node->next;
	}
	ft_free_smatrix(export_split);
	return (1);
}

void export_new(t_mshell *init, char **envp_copy)
{
	t_env *env_node;
	char **export_split;

	export_split = ft_split(init->parser->cmd_exec[1], '=');
	env_node = init->env_table;
	if (var_exists(init, env_node, envp_copy) == 0)
		return;
	while (env_node->next)
		env_node = env_node->next;
	env_node->next = (t_env *)malloc(sizeof(t_env));
	env_table_init(env_node->next);
	env_node = env_node->next;
	env_node->var = ft_strdup(export_split[0]);
	if (export_split[1])
		env_node->content = ft_strdup(export_split[1]);
	ft_free_smatrix(export_split);
	envp_copy = update_envp_copy(init, envp_copy);
}

void export(t_mshell *init, char **envp_copy)
{
	t_env *env_node;
	t_env *prnt;
	t_env *count;
	t_env *stash;
	int flag;

	if (!init->parser->cmd_exec[1])
	{
		stash = (t_env *)malloc(sizeof(t_env));
		env_table_init(stash);
		env_node = assign_val(&count, &flag, init);
		while (count)
		{
			sort_list(&prnt, env_node, init, stash);
			check_oldpwd(prnt, &flag);
			if (strcmp(prnt->var, "_") != 0 && prnt->visibility == 0)
				ft_printf("declare -x %s=\"%s\"\n", prnt->var, prnt->content);
			save_in_stash(prnt, stash);
			env_node = init->env_table;
			count = count->next;
		}
		free_env(stash);
	}
	else
		export_new(init, envp_copy);
}
