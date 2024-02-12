/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 09:58:13 by tiaferna          #+#    #+#             */
/*   Updated: 2024/02/12 10:23:35 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_PWD(t_mshell *init)
{
	t_env	*node;

	node = init->env_table;
	while (node && ft_strcmp("PWD", node->var) != 0)
		node = node->next;
	if (!node)
		return (NULL);
	return (node->content);
}

char	*get_HOME(t_mshell *init)
{
	t_env	*node;

	node = init->env_table;
	while (node && ft_strcmp("HOME", node->var) != 0)
		node = node->next;
	if (!node)
		return (NULL);
	return (node->content);
}

void	create_OLDPWD_node(t_env *node)
{
	node->next = (t_env *)malloc(sizeof(t_env));
	node->next->var = ft_strdup("OLDPWD");
}

void	cd_error_checker(t_mshell *init, t_parser *parser, int *exit_code)
{
	//t_env	*node;

	//node = init->env_table;
	if (parser->cmd_exec[2])
	{
		printf("bash: cd: too many arguments\n");
		*exit_code = 1;
		exit(1);
	}
	else if (parser->cmd_exec[1] == NULL && get_HOME(init) == NULL)
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
		new_dir = ft_strdup(get_HOME(init));
	else
	{
		chdir(parser->cmd_exec[1]);
		new_dir = getcwd(NULL, 0);
	}
	node->content = ft_strdup(new_dir);
	if (get_PWD(init))
	{
		while (ft_strcmp("OLDPWD", node->var) != 0)
		{
			if (!node->next)
				create_OLDPWD_node(node);
			node = node->next;
		}
		free(node->content);
		node->content = ft_strdup(old_dir);
		free(old_dir);
	}
	else
	{
		while (ft_strcmp("OLDPWD", node->var) != 0)
			node = node->next;
	}
}
