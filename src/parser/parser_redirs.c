/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:56:54 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/02/05 12:44:48 by jrocha-v         ###   ########.fr       */
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

/* Change to pipe routing instead of new temp file */
void	clean_here_doc(void)
{
	unlink("here_doc");
	ft_error("minishell: here_doc error", ERROR); 
}

/* Change to pipe routing instead of new temp file */
int		process_here_doc(t_mshell *init, char *eof)
{
	int		file_fd;
	char	*input;
	int		export;

	file_fd = open("here_doc", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (file_fd == -1)
		clean_here_doc();
	while (1)
	{
		ft_putstr_fd(">", init->og_stdout);
		input = get_next_line(init->og_stdin);
		if (!input)
			perror("minishell: input error");
		if (ft_strlen(input) == (ft_strlen(eof) + 1) && \
			ft_strncmp(input, eof, ft_strlen(eof)) == 0)
		{
			free(input);
			break ;
		}
		ft_putstr_fd(input, file_fd);
		free(input);
	}
	close(file_fd);
	export = process_file(init, "here_doc", IN_FILE);
	return (export);
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
	if (!ft_strcmp(file_name, "here_doc"))
		unlink("here_doc");
	return (export);
}
