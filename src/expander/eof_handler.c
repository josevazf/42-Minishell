/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:37:04 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/11 12:45:47 by jrocha-v         ###   ########.fr       */
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
		if (init->eof)
			free(init->eof);
		init->eof = ft_strldup(eof + 1, ft_strlen(eof) - 2);
	}
	else
	{
		if (init->eof)
			free(init->eof);
		init->eof = ft_strdup(eof);
	}
	return (init->eof);
}
