/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 08:04:58 by tiaferna          #+#    #+#             */
/*   Updated: 2024/02/13 12:18:52 by jrocha-v         ###   ########.fr       */
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
