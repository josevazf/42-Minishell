/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:37:04 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/11 12:42:37 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*settle_eof(t_mshell *init, char *eof)
{
	init->expand_heredoc = true;
	if ((eof[0] == '\'' && eof[ft_strlen(eof) - 1] == '\'') || \
	(eof[0] == '\"' && eof[ft_strlen(eof) - 1] == '\"'))
	{
		init->expand_heredoc = false;
		init->eof = ft_strldup(eof + 1, ft_strlen(eof) - 2);
	}
	else
		init->eof = ft_strdup(eof);
	return (init->eof);
}
