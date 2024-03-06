/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_var_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:34:51 by tiaferna          #+#    #+#             */
/*   Updated: 2024/03/06 15:41:30 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_new_var(t_mshell *init, char ***envp_copy)
{
	int		i;
	int		j;
	t_env	*node;

	i = 0;
	j = 0;
	printf("ENTROU\n");
	node = init->env_table;
	while (node->next)
		node = node->next;
	node->next = (t_env *)malloc(sizeof(t_env));
	node = node->next;
	env_table_init(node);
	node->visibility = 1;
	while (ft_iswhitespace(init->in[i]))
		i++;
	while (init->in[i + j] != '=')
		j++;
	node->var = ft_strldup(init->in + i, j);
	i = j + 1;
	j = 0;
	while (init->in[i + j] && !ft_iswhitespace(init->in[i + j]))
		j++;
	if (!init->in[i + j])
		node->content = ft_strldup(init->in + i, j);
	*envp_copy = update_envp_copy(init, envp_copy);
}

int	empty_input(t_mshell *init)
{
	free(init->in);
	init->in = ft_strdup("");
	return (1);
}

void	set_content(t_mshell *init, t_env *node, int i, int j)
{
	while (init->in[i + j] && !ft_iswhitespace(init->in[i + j]))
		j++;
	if (!init->in[i + j])
		node->content = ft_strldup(init->in + i, j);
}

int	var_is_set(t_mshell *init, char ***envp_copy)
{
	int		i;
	int		j;
	t_env	*node;

	i = 0;
	j = 0;
	node = init->env_table;
	while (ft_iswhitespace(init->in[i]))
		i++;
	while (init->in[i + j] != '=')
		j++;
	printf("j: %d\n", j);
	while (node)
	{
		printf("node->var: %s\n", node->var);
		if (ft_strncmp(init->in + i, node->var, j) == 0 && !node->var[j])
		{
			node->visibility = 0;
			i = j + 1;
			j = 0;
			set_content(init, node, i, j);
			*envp_copy = update_envp_copy(init, envp_copy);
			return (0);
		}
		node = node->next;
	}
	return (1);
}

int	new_var_checker(t_mshell *init, char ***envp_copy)
{
	int	i;

	i = 0;
	while (ft_iswhitespace(init->in[i]))
		i++;
	if (ft_strncmp(init->in + i, "export=", 7) == 0)
		return (empty_input(init));
	while (ft_isalnum(init->in[i]))
		i++;
	if (init->in[i] == '=')
	{
		if (init->in[i + 1] == '\0')
			return (empty_input(init));
		if (var_is_set(init, envp_copy) == 1)
			create_new_var(init, envp_copy);
		return (0);
	}
	return (1);
}
