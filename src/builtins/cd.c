/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 09:58:13 by tiaferna          #+#    #+#             */
/*   Updated: 2024/02/12 16:20:37 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_home(t_mshell *init)
{
	t_env	*node;

	node = init->env_table;
	while (node && ft_strcmp("HOME", node->var) != 0)
		node = node->next;
	if (!node)
		return (NULL);
	return (node->content);
}

void	create_oldpwd_node(t_env *node)
{
	node->next = (t_env *)malloc(sizeof(t_env));
	node->next->var = ft_strdup("OLDPWD");
}

void	update_dir(t_parser *parser, char *new_dir)
{
	chdir(parser->cmd_exec[1]);
	new_dir = getcwd(NULL, 0);
}

void	cd_error_checker(t_mshell *init, t_parser *parser, int *exit_code)
{
	if (parser->cmd_exec[2] != NULL)
	{
		printf("bash: cd: too many arguments\n");
		*exit_code = 1;
		exit(1);
	}
	else if (parser->cmd_exec[1] == NULL && get_home(init) == NULL)
	{
		printf("bash: cd: HOME not set\n");
		*exit_code = 1;
		exit(1);
	}
}

void	cd(t_mshell *init, t_parser *parser, int *exit_code)
{
	t_env	*node;
	char	*old_dir;
	char	*new_dir;

	cd_error_checker(init, parser, exit_code);
	new_dir = NULL;
	node = init->env_table;
	old_dir = ft_strdup(getcwd(NULL, 0));
	if (parser->cmd_exec[1] == NULL)
		new_dir = ft_strdup(get_home(init));
	else
		update_dir(parser, new_dir);
	node->content = ft_strdup(new_dir);
	free(new_dir);
	while (ft_strcmp("OLDPWD", node->var) != 0)
	{
		if (!node->next)
			create_oldpwd_node(node);
		node = node->next;
	}
	free(node->content);
	node->content = ft_strdup(old_dir);
	free(old_dir);
	exit(0);
}
