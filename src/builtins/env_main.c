/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:28:50 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/02/26 22:07:36 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Duplicates envp */

char	**envp_dup(char **envp)
{
	int		i;
	char	**envp_copy;
	
	i = 0;
	while (envp[i])
		i++;
	envp_copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envp_copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		envp_copy[i] = ft_strdup(envp[i]);
		i++;
	}
	envp_copy[i] = NULL;
	return (envp_copy);
}

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

/* Updates de envp_copy variable to reflect any changes made to it */
char	**update_envp_copy(t_mshell *init, char ***envp_copy)
{
	int	i;
	t_env	*node;
	
	i = 0;
	node = init->env_table;
	while (node && i++ >= 0)
		node = node->next;
	ft_free_smatrix(*envp_copy);
	(*envp_copy) = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	node = init->env_table;
	while (node)
	{
		(*envp_copy)[i] = ft_strdup(node->var);
		if (node->visibility == 1 && node->var[ft_strlen(node->var) - 1] != '~')
			(*envp_copy)[i] = ft_strupdate((*envp_copy)[i], "~");
		if (node->content)
		{	
			(*envp_copy)[i] = ft_strupdate((*envp_copy)[i], "=");
			(*envp_copy)[i] = ft_strupdate((*envp_copy)[i], node->content);
		}
		i++;
		node = node->next;
	}
	(*envp_copy)[i] = NULL;
	return (*envp_copy);
}

/* Creates env node */

t_env	*create_env_node(char *var, char *content)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	env_table_init(node);
	node->var = ft_strdup_env(var);
	if (content)
		node->content = ft_strdup(content);
	if (var[ft_strlen(var) - 1] == '~')
		node->visibility = 1;
	else
		node->visibility = 0;
	return (node);
}

/* Places new env node at the end of the list */
void	env_node_push_back(t_env *begin_list, char *var, char *content)
{
	t_env	*node;
	
	node = begin_list;
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = create_env_node(var, content);
	}
	else
		begin_list = create_env_node(var, content);
}

/* Creates linked list with values from envp */
int		*create_env_list(t_mshell *init, char **envp_copy)
{
	int		i;
	char	**temp;
	t_env	*env_list;

	i = 0;
	while ((envp_copy)[i]) 
	{
		temp = ft_split((envp_copy)[i], '=');

		if (i == 0)
			env_list = create_env_node(temp[0], temp[1]);
		else
			env_node_push_back(env_list, temp[0], temp[1]);
		ft_free_smatrix(temp);
		i++;
	}
	init->env_table = env_list;
	return (0);
}
