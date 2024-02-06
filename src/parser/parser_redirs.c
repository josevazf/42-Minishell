/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:56:54 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/02/06 12:25:22 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirs_router(t_mshell *init, char *redirs)
{
	char	**redirs_full;
	
	redirs_full = ft_split(redirs, '\t');
	if (redirs_full[1] == NULL)
	{
		ft_free_smatrix(redirs_full);
		redirs_error();
		return ;
	}
	if (!ft_strncmp(redirs_full[0], "<<", 2))
		init->red_input = process_here_doc(init, redirs_full[1]);	
	else if (!ft_strncmp(redirs_full[0], "<", 1))
		init->red_input = process_file(init, redirs_full[1], IN_FILE);
	else if (!ft_strncmp(redirs_full[0], ">>", 2))
		init->red_output = process_file(init, redirs_full[1], OUT_FILE_APND);
	else if (!ft_strncmp(redirs_full[0], ">", 1))
		init->red_output = process_file(init, redirs_full[1], OUT_FILE_OWR);
	ft_free_smatrix(redirs_full);
}

/* Get here_doc input and write to pipe */
void	write_here_doc(t_mshell *init, char *eof, int *pipe_fd)
{
	char	*input;

	ft_putstr_fd(">", init->og_stdout);
	input = get_next_line(init->og_stdin);
	if (!input) 
	{
		perror("minishell: input error");
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (ft_strlen(input) == (ft_strlen(eof) + 1) &&
		ft_strncmp(input, eof, ft_strlen(eof)) == 0)
	{
		free(input);
		close(pipe_fd[1]);
		exit(EXIT_SUCCESS);
	}
	write(pipe_fd[1], input, ft_strlen(input));
	free(input);
}

/* Process here_doc */
int		process_here_doc(t_mshell *init, char *eof)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		export;
	int		status;

	if (pipe(pipe_fd) == -1)
		ft_error("minishell: failed creating pipe", ERROR); /* FIXXXXX */
	pid = fork();
	if (pid == -1)
		ft_error("minishell: failed creating fork", ERROR); /* FIXXXXX */
	if (pid == 0)
	{
		close(pipe_fd[0]);
        while (1) 
			write_here_doc(init, eof, pipe_fd);
	}
	else
	{
        close(pipe_fd[1]);
		export = dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
        waitpid(pid, &status, 0);
        return (export);
	}
}

int	process_file(t_mshell *init, char *file_name, int file_type)
{
	int	file_fd;
	int	export;

	(void)init;
	if (file_type == IN_FILE)
		file_fd = open(file_name, O_RDONLY);
	if (file_type == OUT_FILE_OWR)
		file_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_type == OUT_FILE_APND)
		file_fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file_fd == -1)
		file_error(file_name);  /* FIXXXXX */
	if (file_type == IN_FILE)
		export = dup2(file_fd, STDIN_FILENO);
	if (file_type != IN_FILE)
		export = dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	return (export);
}
