/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:49:24 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/29 10:52:41 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



/* Helper function to free Parser variables */
void	free_parser_temps(char *cmds, char *redirs, char *cmd_path)
{
	free(cmds);
	free(redirs);
	free(cmd_path);
}

/* Helper function to free Parser variables */
void	free_parser_vars(char **cmds, char **redirs)
{
	*cmds = NULL;
	*redirs = NULL;
	free(*cmds);
	free(*redirs);
}