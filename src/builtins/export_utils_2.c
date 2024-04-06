/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:33:59 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/06 13:04:05 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_content(char **export_split, t_env *env_node)
{
	int	j;

	j = 1;
	env_node->content = ft_strdup(export_split[j]);
	if (!export_split[j + 1])
		return ;
	while (export_split[++j])
	{
		env_node->content = ft_strupdate(env_node->content, "=");
		env_node->content = ft_strupdate(env_node->content, export_split[j]);
	}
	return ;
}
