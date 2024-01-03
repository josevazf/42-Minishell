/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:28:50 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/03 11:43:42 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Creates env node */
t_env	*create_env_node(char *var, char *content)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->var = ft_strdup(var);
	node->content = ft_strdup(content);
	node->next = NULL;
	return (node);
}

/* Places new env node at the end of the list */
void	env_node_push_back(t_env **begin_list, char *var, char *content)
{
	t_env	*node;
	
	node = *begin_list;
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = create_env_node(var, content);
	}
	else
		*begin_list = create_env_node(var, content);
}

/* Creates linked list with values from envp */
t_env	*create_env_list(char **envp, int i)
{
	int		nb_lines;
	char 	*var;
	char	*content;
	char	**temp;
	t_env	*env_list;

	nb_lines = 0;
	while (envp[++i])
		nb_lines++;
	i = -1;
	while (++i <= nb_lines) 
	{
		temp = ft_split(envp[i], '=');
		var = ft_strdup(temp[0]);
		content = ft_strdup(ft_strpbrk(envp[i], "=") + 1);
		if (i == 0)
			env_list = create_env_node(var, content);
		else
			env_node_push_back(&env_list, var, content);
		ft_free_smatrix(temp);
		free(var);
		free(content);
	}
	return (env_list);
}
