/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:49:24 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/19 10:03:33 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Helper function to free Parser variables */
void	free_parser_temps(char *cmd_path, char *cmd_temp)
{
	free(cmd_path);
	free(cmd_temp);
}
