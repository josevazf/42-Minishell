/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 08:04:58 by tiaferna          #+#    #+#             */
/*   Updated: 2024/03/20 17:40:30 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(t_parser *parser)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	write(parser->output, dir, ft_strlen(dir));
	write(parser->output, "\n", 1);
	exit(EXIT_SUCCESS);
}
