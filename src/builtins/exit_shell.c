/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:21:50 by guest             #+#    #+#             */
/*   Updated: 2024/02/13 12:18:34 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_ms(t_mshell *init)
{
	delete_lists(init);
	rl_clear_history();
	ft_printf("Exit\n");
	exit(EXIT_SUCCESS);
}