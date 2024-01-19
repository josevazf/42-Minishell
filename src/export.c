/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:22:25 by patatoss          #+#    #+#             */
/*   Updated: 2024/01/19 00:10:15 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	export_new(t_mshell *init)
{
	t_lexer	*lexer_node;
	t_env	*env_node;
	size_t	i;

	lexer_node = init->lexer->next;
	env_node = init->env_table;
	while (env_node->next)
		env_node = env_node->next;
	while (lexer_node)
	{
		env_node->next = (t_env *)malloc(sizeof(t_env));
		env_table_init(env_node->next);
		env_node = env_node->next;
		i = 0;
		while (lexer_node->str[i] && lexer_node->str[i] != '=')
			i++;
		if (i == ft_strlen(lexer_node->str))
			env_node->var = ft_strdup(lexer_node->str);
		else
		{
			env_node->var = ft_strldup(lexer_node->str, i);
			env_node->content = ft_strndup(lexer_node->str, i + 1);
		}
		lexer_node = lexer_node->next;
	}
}

void	export(t_mshell *init)
{
	t_env	*env_node;
	t_env	*prnt;
	t_env	*count;
	t_env	*stash;
	int		flag;

	if (!init->lexer->next)
	{
		stash = (t_env *)malloc(sizeof(t_env));
		env_table_init(stash);
		assign_val(&env_node, &count, &flag, init);
		while (count)
		{
			sort_list(&prnt, env_node, init, stash);
			check_oldpwd(prnt, &flag);
			if (strcmp(prnt->var, "_") != 0)
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
