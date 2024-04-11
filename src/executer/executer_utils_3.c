/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:20:37 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/11 09:31:22 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	safe_closedir(DIR *dir)
{
	if (dir != NULL)
		closedir(dir);
}

void	safe_closedir_fd(DIR *dir, int fd)
{
	if (dir != NULL)
		closedir(dir);
	if (fd < 0)
		return ;
	close(fd);
}
