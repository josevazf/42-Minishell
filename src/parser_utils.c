/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:49:24 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/29 16:07:45 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_redirs(char *og_redirs, t_lexer **lexer)
{
	if (!og_redirs)
	{
		og_redirs = ft_strdup((*lexer)->str);
		(*lexer) = (*lexer)->next;
		og_redirs = parser_merge_split(og_redirs, (*lexer)->str);
	}
	else
	{
		og_redirs = ft_strupdate(og_redirs, (*lexer)->str);
		(*lexer) = (*lexer)->next;
		og_redirs = parser_merge_split(og_redirs, (*lexer)->str);
	}
	return (og_redirs);
}

char	*parser_merge_split(char *og_str, char *lexer_str)
{
	og_str = ft_strupdate(og_str, "\t");
	og_str = ft_strupdate(og_str, lexer_str);
	og_str = ft_strupdate(og_str, "\t");
	return (og_str);
}

/* Helper function to free Parser variables */
void	free_parser_temps(char *cmds, char *redirs, char *cmd_path, 
												char **cmd_full)
{
	free(cmds);
	free(redirs);
	free(cmd_path);
	ft_free_smatrix(cmd_full);
}

/* Helper function to free Parser variables */
void	free_parser_vars(char **cmds, char **redirs)
{
	*cmds = NULL;
	*redirs = NULL;
	free(*cmds);
	free(*redirs);
}