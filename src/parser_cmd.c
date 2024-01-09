/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 08:29:36 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/09 12:05:09 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

/* Return the type of the command, Shell native or Builtin */
int		cmd_router(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0 ||
		ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0 ||
		ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0 || 
		ft_strcmp(cmd, "exit") == 0)
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

char	*find_cmd(char *cmd)
{
	char	**paths;
	char	*cmd_path;
	
	paths = parse_path(getenv("PATH"));
	cmd_path = get_cmd_path(paths, cmd);
	if (cmd_path == NULL)
	{
		ft_free_smatrix(paths);
		free(cmd_path);
		ft_printf(ft_strjoin(cmd, ": command not found\n"));
		return ("hello");
	}
	ft_free_smatrix(paths);
	return (cmd_path);
}
