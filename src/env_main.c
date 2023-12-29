/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:28:50 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/12/29 08:52:03 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*create_node(char *var, char *content)
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

void	node_push_back(t_env **begin_ll, char *var, char *content)
{
	t_env	*node;
	
	node = *begin_ll;
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = create_node(var, content);
	}
	else
		*begin_ll = create_node(var, content);
}

// Creates linked list with values from envp
t_env	*create_envll(char **envp, int i)
{
	int		nb_lines;
	char 	*var;
	char	*content;
	char	**temp;
	t_env	*envll;

	nb_lines = 0;
	while (envp[++i])
		nb_lines++;
	i = -1;
	while (++i < nb_lines) 
	{
		temp = ft_split(envp[i], '=');
		var = ft_strdup(temp[0]);
		content = ft_strdup(temp[1]);
		if (i == 0)
			envll = create_node(var, content);
		else
			node_push_back(&envll, var, content);
		ft_free_smatrix(temp);
		free(var);
		free(content);
	}
	return (envll);
}
