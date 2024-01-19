/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 09:58:13 by tiaferna          #+#    #+#             */
/*   Updated: 2024/01/19 10:01:36 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd(t_mshell *init)
{
	t_env	*node;
	char	*old_dir;
	char	*new_dir;

	new_dir = NULL;
	node = init->env_table;
	while(node && ft_strcmp("PWD", node->var) != 0)
		node = node->next;
	old_dir = ft_strdup(node->content);
	free(node->content);
	chdir(init->lexer->next->str);
	new_dir = getcwd(NULL, 0);
	node->content = ft_strdup(new_dir);
	while(ft_strcmp("OLDPWD", node->var) != 0)
	{
		if (!node->next)
		{
			node->next = (t_env *)malloc(sizeof(t_env));
			node->next->var = ft_strdup("OLDPWD");
		}
		node = node->next;
	}
	free(node->content);
	node->content = ft_strdup(old_dir);
	free(old_dir);
}
