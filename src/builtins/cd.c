/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 09:58:13 by tiaferna          #+#    #+#             */
/*   Updated: 2024/02/12 17:41:47 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_home(t_mshell *init)
{
	t_env	*node_home;
	t_env	*node_pwd;

	node_home = init->env_table;
	while (node_home && ft_strcmp("HOME", node_home->var) != 0)
		node_home = node_home->next;
	if (!node_home)
		return (NULL);
	node_pwd = init->env_table;
	while (node_pwd && ft_strcmp("PWD", node_pwd->var) != 0)
		node_pwd = node_pwd->next;
	if (ft_strcmp("PWD", node_pwd->var) == 0)
	{
		free(node_pwd->content),
		node_pwd->content = ft_strdup(node_home->content);
	}
	return (node_home->content);
}

void	create_oldpwd_node(t_env *node)
{
	node->next = (t_env *)malloc(sizeof(t_env));
	node->next->var = ft_strdup("OLDPWD");
	node->next->content = NULL;
	node->next->next = NULL;
}

void	update_dir(t_parser *parser, char **new_dir, t_env *node)
{
	char	*file_err;

	if (chdir(parser->cmd_exec[1]) != 0)
	{
		file_err = strerror(errno);
		printf("minishell: %s: %s\n", parser->cmd_exec[1], file_err);
	}
	*new_dir = getcwd(NULL, 0);
	free(node->content);
	node->content = ft_strdup(*new_dir);
}

void	cd_error_checker(t_mshell *init, t_parser *parser, int *exit_code)
{
	if (parser->cmd_exec[1] != NULL)
	{
		if (parser->cmd_exec[2] != NULL)
		{
			printf("minishell: cd: too many arguments\n");
			*exit_code = 1;
		}
	}
	else if (parser->cmd_exec[1] == NULL && get_home(init) == NULL)
	{
		printf("minishell: cd: HOME not set\n");
		*exit_code = 1;
	}
}

void	cd(t_mshell *init, t_parser *parser, int *exit_code)
{
	t_env	*node;
	char	*old_dir;
	char	*new_dir;

	cd_error_checker(init, parser, exit_code);
	node = init->env_table;
	old_dir = getcwd(NULL, 0);
	if (parser->cmd_exec[1] == NULL)
	{
		new_dir = ft_strdup(get_home(init));
		chdir(new_dir);
	}
	else
		update_dir(parser, &new_dir, node);
	free(new_dir);
	while (ft_strcmp("OLDPWD", node->var) != 0)
	{
		if (!node->next)
			create_oldpwd_node(node);
		node = node->next;
	}
	if (node->content)
		free(node->content);
	node->content = ft_strdup(old_dir);
	free(old_dir);
}
