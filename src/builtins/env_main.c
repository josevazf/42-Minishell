/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:28:50 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/08 20:08:41 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Duplicates envp */
char	*ft_strdup_env(const char *str)
{
	char	*temp;

	if (str[ft_strlen(str) - 1] == '~')
	{
		temp = ft_strldup(str, ft_strlen(str) - 1);
		return (temp);
	}
	else
	{
		temp = ft_strdup(str);
		return (temp);
	}
}

/* Creates env node */
t_env	*create_env_node(char **temp)
{
	t_env	*node;
	int		i;

	i = 1;
	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	env_table_init(node);
	node->var = ft_strdup_env(temp[0]);
	if (temp[i])
		node->content = ft_strdup(temp[i]);
	while (temp[++i])
	{
		node->content = ft_strupdate(node->content, "=");
		node->content = ft_strupdate(node->content, temp[i]);
	}
	if (temp[0][ft_strlen(temp[0]) - 1] == '~')
		node->visibility = 1;
	else
		node->visibility = 0;
	return (node);
}

/* Places new env node at the end of the list */
void	env_node_push_back(t_env *begin_list, char **temp)
{
	t_env	*node;

	node = begin_list;
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = create_env_node(temp);
	}
	else
		begin_list = create_env_node(temp);
}

/* Creates linked list with values from envp */
int	*create_env_list(t_mshell *init, char **envp_copy)
{
	int		i;
	char	**temp;
	t_env	*env_list;

	i = 0;
	init->env_table = NULL;
	while ((envp_copy)[i])
	{
		temp = ft_split((envp_copy)[i], '=');
		if (i == 0)
			env_list = create_env_node(temp);
		else
			env_node_push_back(env_list, temp);
		ft_free_smatrix(temp);
		i++;
	}
	init->env_table = env_list;
	return (0);
}
