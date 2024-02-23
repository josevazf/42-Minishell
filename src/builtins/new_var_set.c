/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_var_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:34:51 by tiaferna          #+#    #+#             */
/*   Updated: 2024/02/21 11:06:57 by tiaferna         ###   ########.fr       */
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
	*envp_copy = update_envp_copy(init, *envp_copy);
}

void	new_var_checker(t_mshell *init, char ***envp_copy)
{
	int	i;

	i = 0;
	while (ft_iswhitespace(init->in[i]))
		i++;
	if (!ft_isalnum(init->in[i]))
		return;
	while (ft_isalnum(init->in[i]))
		i++;
	if (init->in[i] == '=')
		create_new_var(init, envp_copy);
	return;
}
