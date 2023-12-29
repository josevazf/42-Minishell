/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 09:58:13 by tiaferna          #+#    #+#             */
/*   Updated: 2023/12/29 12:42:30 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	cd(t_mshell *init, char	**envp)
{
	t_env	*env_head;
	char	*old_dir;
	int		i;
	
	env_head = init->env_table;
	while(ft_strcmp("PWD", init->env_table->var) != 0)
		init->env_table = init->env_table->next;
	old_dir = ft_strdup(init->env_table->content);
	free(init->env_table->content);
	chdir(init->lexer->next->str); // Tratar em caso de erro
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PWD=", 4))
		{
			ft_printf("%s\n", envp[i]);
			init->env_table->content = ft_strdup(envp[i] + 4);
		}
		i++;
	}
	ft_printf("PWD = %s\n", init->env_table->content);
	while(ft_strcmp("OLDPWD", init->env_table->var) == 6)
		init->env_table = init->env_table->next;
	free(init->env_table->content);
	init->env_table->content = ft_strdup(old_dir);
	free(old_dir);
	ft_printf("OLDPWD = %s\n", init->env_table->content);
	init->env_table = env_head;
}
