/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:28:50 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/02/21 12:45:18 by tiaferna         ###   ########.fr       */
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

/* Updates de envp_copy variable to reflect any changes made to it */
char	**update_envp_copy(t_mshell *init, char **envp_copy)
{
	int	i;
	t_env	*node;
	
	i = 0;
	node = init->env_table;
	while (node && i++ >= 0)
		node = node->next;
	ft_free_smatrix(envp_copy);
	envp_copy = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	node = init->env_table;
	while (node)
	{
		envp_copy[i] = ft_strdup(node->var);
		if (node->visibility == 1)
			envp_copy[i] = ft_strupdate(envp_copy[i], "~");
		envp_copy[i] = ft_strupdate(envp_copy[i], "=");
		envp_copy[i] = ft_strupdate(envp_copy[i], node->content);
		i++;
		node = node->next;
	}
	envp_copy[i] = NULL;
	return (envp_copy);
}

/* Creates env node */

t_env	*create_env_node(char *var, char *content, char *str)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->var = ft_strdup(var);
	node->content = ft_strdup(content);
	if (str[ft_strlen(str) - 1] == '~')
		node->visibility = 1;
	else
		node->visibility = 0;
	node->next = NULL;
	return (node);
}

/* Places new env node at the end of the list */
void	env_node_push_back(t_env **begin_list, char *var, char *content, char *str)
{
	t_env	*node;
	
	node = *begin_list;
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = create_env_node(var, content, str);
	}
	else
		*begin_list = create_env_node(var, content, str);
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

/* Creates linked list with values from envp */
int		*create_env_list(t_mshell *init, char **envp_copy, int i)
{
	int		nb_lines;
	char 	*var;
	char	*content;
	char	**temp;
	t_env	*env_list;

	nb_lines = 0;
	while (envp_copy[++i])
		nb_lines++;
	i = -1;
	while (++i <= nb_lines) 
	{
		temp = ft_split(envp_copy[i], '=');
		var = ft_strdup_env(temp[0]);
		content = ft_strdup(ft_strpbrk(envp_copy[i], "=") + 1);
		if (i == 0)
			env_list = create_env_node(var, content, temp[0]);
		else
			env_node_push_back(&env_list, var, content, temp[0]);
		ft_free_smatrix(temp);
		free(var);
		free(content);
	}
	init->env_table = env_list;
	return (0);
}
