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
	node->next->content = NULL;
	node->next->next = NULL;
}

void	update_dir(t_parser *parser, char **new_dir)
{
	char	*file_err;

	if (chdir(parser->cmd_exec[1]) != 0)
		{
			file_err = strerror(errno);
			printf("minishell: %s: %s\n", parser->cmd_exec[1], file_err);
		}
	*new_dir = getcwd(NULL, 0);
}

void	cd_error_checker(t_mshell *init, t_parser *parser, int *exit_code)
{	
	if (parser->cmd_exec[2] != NULL)
	{
		printf("minishell: cd: too many arguments\n");
		*exit_code = 1;
	}
	else if (parser->cmd_exec[1] == NULL && get_home(init) == NULL)
	{
		printf("minishell: cd: HOME not set\n");
		*exit_code = 1;
	}
}


void	cd(t_mshell *init, t_parser *parser, int *exit_code)
{
	t_env	*node_head;
	char	*old_dir;
	char	*new_dir;

	cd_error_checker(init, parser, exit_code);
	new_dir = NULL;
	node_head = init->env_table;
	old_dir = getcwd(NULL, 0);
	if (parser->cmd_exec[1] == NULL)
		new_dir = ft_strdup(get_home(init));
	else
		update_dir(parser, &new_dir);
	init->env_table->content = ft_strdup(new_dir);
	free(new_dir);
	while (ft_strcmp("OLDPWD", init->env_table->var) != 0)
	{
		if (!init->env_table->next)
			create_oldpwd_node(init->env_table);
		init->env_table = init->env_table->next;
	}
	if (init->env_table->content)
		free(init->env_table->content);
	init->env_table->content = ft_strdup(old_dir);
	free(old_dir);
	init->env_table = node_head;
}
