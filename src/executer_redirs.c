/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:56:54 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/19 10:02:02 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*						WWWWIIIIIPPPPP 							*/

void	process_dev_urandom(void)
{
	int		urandom_fd;
	int		temp_fd;
	int		i;
	char	*input;

	i = 0;
	urandom_fd = open("/dev/urandom", O_RDONLY);
	temp_fd = open("temp_urandom.txt", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (urandom_fd == -1 || temp_fd == -1)
		ft_error("minishell: file error", ERROR);
	while (++i < 50)
	{
		input = get_next_line(urandom_fd);
		if (!input)
			ft_error("minishell: input error", 1);
		ft_putstr_fd(input, temp_fd);
		free(input);
		ft_printf("%i", i);
	}
	close(urandom_fd);
	close(temp_fd);
	process_file("temp_urandom.txt", IN_FILE);
}

/* Change to pipe routing instead of new temp file */
void	clean_here_doc(void)
{
	unlink("here_doc");
	ft_error("minishell: here_doc error", ERROR); 
}

/* Change to pipe routing instead of new temp file */
void	process_here_doc(char **argv)
{
	int		file_fd;
	char	*input;

	file_fd = open("here_doc", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (file_fd == -1)
		clean_here_doc();
	while (1)
	{
		ft_putstr_fd("here_doc>", 1);
		input = get_next_line(0);
		if (!input)
			ft_error("pipex: input error", ERROR);
		if (ft_strlen(input) == (ft_strlen(argv[2]) + 1) && \
			ft_strncmp(input, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(input);
			break ;
		}
		ft_putstr_fd(input, file_fd);
		free(input);
	}
	close(file_fd);
	process_file("here_doc", IN_FILE);
}

void	process_file(char *file_name, int file_type)
{
	int	file_fd;

	if (file_type == IN_FILE)
		file_fd = open(file_name, O_RDONLY);
	if (file_type == OUT_FILE)
		file_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd == -1)
		ft_error("minishell: file error", ERROR);  /* FIXXXXX */
	if (file_type == IN_FILE)
		dup2(file_fd, STDIN_FILENO);
	if (file_type == !IN_FILE)
		dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
}
