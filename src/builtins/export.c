/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:22:25 by patatoss          #+#    #+#             */
/*   Updated: 2024/02/15 14:31:22 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	var_exists(t_mshell *init, t_env *env_node)
{
	char *export_var;
	char *export_content;
	int i;

	i = 7;
	export_content = NULL;
	while (init->in[i] && init->in[i] != '=')
		i++;
	export_var = ft_strldup(init->in + 7, i - 7);
	if (init->in[i])
	{
		i = ft_strlen(init->in);
		while (init->in[i] != '=')
			i--;
		export_content = ft_strdup(init->in + i);
	}
	while (env_node)
	{
		if (ft_strcmp(env_node->var, export_var) == 0 && export_content)
		{
			if (env_node->content)
				free (env_node->content);
			env_node->content = ft_strdup(export_content);
			env_node->visibility = 0;
			return (0);
		}
		env_node = env_node->next;
	}
	return (1);
}

void	export_new(t_mshell *init)
{
	t_env	*env_node;

	env_node = init->env_table;
	if (var_exists(init, env_node) == 0)
		return ;
	while (env_node->next)
		env_node = env_node->next;
	env_node->next = (t_env *)malloc(sizeof(t_env));
	env_table_init(env_node->next);
	env_node = env_node->next;
	env_node->var = ft_strdup(init->parser->cmd_exec[1]);
	if (init->parser->cmd_exec[2] && init->parser->cmd_exec[3])
		env_node->content = ft_strdup(init->parser->cmd_exec[3]);	
}

void	export(t_mshell *init)
{
	t_env	*env_node;
	t_env	*prnt;
	t_env	*count;
	t_env	*stash;
	int		flag;

	if (!init->parser->cmd_exec[1])
	{
		stash = (t_env *)malloc(sizeof(t_env));
		env_table_init(stash);
		assign_val(&env_node, &count, &flag, init);
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
		export_new(init);
}
