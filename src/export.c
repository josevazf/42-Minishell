/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patatoss <patatoss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:22:25 by patatoss          #+#    #+#             */
/*   Updated: 2024/01/04 19:11:42 by patatoss         ###   ########.fr       */
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
		if (ft_strcmp(node->var, stash_node->var) == 0)
			return (0);
		stash_node = stash_node->next;
	}
	return (1);
}

void	export_list()
{

}

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
		env_node->next->var = NULL;
		env_node->next->content = NULL;
		env_node->next->next = NULL;
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
	t_env	*to_print;
	t_env	*count;
	t_env	*stash;
	int		flag;
	
	if (!init->lexer->next)
	{
		stash = (t_env *)malloc(sizeof(t_env));
		stash->var = NULL;
		stash->content = NULL;
		stash->next = NULL;
		env_node = init->env_table;
		count = init->env_table;
		flag = 0;
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
			if (ft_strcmp("OLDPWD", to_print->var) == 0)
				flag = 1;
			if (ft_strcmp("OLDPWD", to_print->var) < 0 && flag == 0)
			{
				flag = 1;
				ft_printf("declare -x OLDPWD\n", to_print->var, to_print->content);
			}
			ft_printf("declare -x %s=\"%s\"\n", to_print->var, to_print->content);
			save_in_stash(to_print, stash);
			env_node = init->env_table;
			count = count->next;
		}
	}
	else
		export_new(init);
}
