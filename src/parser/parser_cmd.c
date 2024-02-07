/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guest <guest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 08:29:36 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/02/07 15:24:12 by guest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Return the type of the command, Shell native or Builtin */
int	cmd_router(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || \
		!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export") || \
		!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") || \
		!ft_strcmp(cmd, "exit"))
		return (BUILTIN_CMD);
	else
		return (SHELL_CMD);
}

char	**parse_path(char *env_path)
{
	char	**paths;

	paths = ft_split(env_path, ':');
	if (paths == NULL)
		return (NULL);
	return (paths);
}

/* Get the full path for the command to execute */
char	*get_cmd_path(char **envp_paths, char *cmd)
{
	char	*temp_path;
	char	*new_path;
	int		i;

	i = 0;
	while (envp_paths[++i])
	{
		temp_path = ft_strjoin(envp_paths[i], "/");
		if (temp_path == NULL)
			return (NULL);
		new_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (new_path == NULL)
			return (NULL);
		if (access(new_path, X_OK) == 0)
			return (new_path);
		free(new_path);
	}
	return (NULL);
}

/* Check if command exists and return it's path */
char	*find_cmd(char *cmd, t_mshell *init)
{
	char	**paths;
	char	*cmd_path;
	char	*error_msg;

	init->cmd_not_found = false;
	paths = parse_path(getenv("PATH"));
	if (access(cmd, F_OK | X_OK) == 0)
		cmd_path = ft_strdup(cmd);
	else
		cmd_path = get_cmd_path(paths, cmd);
	if (cmd_path == NULL)
	{
		ft_free_smatrix(paths);
		error_msg = ft_strjoin(cmd, ": command not found\n");
		ft_printf(error_msg);
		free(error_msg);
		init->cmd_not_found = true;
		return (NULL);
	}
	ft_free_smatrix(paths);
	return (cmd_path);
}
