/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 08:29:36 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/12/08 14:46:43 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

// Find 'PATH=' in envp file and return the paths delimited by ':'
char	**parse_path(char **envp)
{
	char	*envp_dup;
	char	**paths;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (envp[i] == NULL)
		return (NULL);
	envp_dup = ft_strdup(envp[i] + 5);
	if (envp_dup == NULL)
		return (NULL);
	paths = ft_split(envp_dup, ':');
	free(envp_dup);
	if (paths == NULL)
		return (NULL);
	return (paths);
}

// Get the full path for the command to execute
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

// TO UPDATEEEEE
char	find_cmd(char *argv, char **envp)
{
	char	**cmd;
	char	**paths;
	char	*cmd_path;

	cmd = ft_split(argv, ' ');
	paths = parse_path(envp);
	cmd_path = get_cmd_path(paths, cmd[0]);
	if (cmd_path == NULL)
	{
		ft_free_smatrix(cmd);
		ft_free_smatrix(paths);
		free(cmd_path);
		ft_error(ft_strjoin("minishell: ", argv), CMD_NOT_FOUND);
	}
	ft_free_smatrix(cmd);
	ft_free_smatrix(paths);
	free(cmd_path);
	
}
