/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:28:50 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/01 17:54:27 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_shlvl(t_mshell *init)
{
	t_env	*node;
	char	*temp;
	int		val;

	node = init->env_table;
	while (node && ft_strcmp(node->var, "SHLVL") != 0)
	{
		if (node->next == NULL)
		{
			printf("vazio\n");
			create_env_node("SHLVL", "1");
			return ;
		}
		node = node->next;
	}
	val = ft_atoi(node->content) + 1;
	free(node->content);
	temp = ft_itoa(val);
	node->content = ft_strdup(temp);
	free(temp);
}

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
			env_list = create_env_node(temp[0], temp[1]);
		else
			env_node_push_back(env_list, temp[0], temp[1]);
		ft_free_smatrix(temp);
		i++;
	}
	init->env_table = env_list;
	set_shlvl(init);
	return (0);
}
