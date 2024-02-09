/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 08:04:58 by tiaferna          #+#    #+#             */
/*   Updated: 2024/01/19 12:00:33 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(t_parser *parser)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	write(parser->output, dir, ft_strlen(dir));
	write(parser->output, "\n", 1);
}
