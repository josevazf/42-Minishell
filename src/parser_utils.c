/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:49:24 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/25 10:47:58 by jrocha-v         ###   ########.fr       */
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
