/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guest <guest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:21:50 by guest             #+#    #+#             */
/*   Updated: 2024/02/07 14:30:49 by guest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_ms(t_mshell *init)
{
	delete_lists(init);
	rl_clear_history();
	ft_printf("Exit\n");
	exit(0);
}