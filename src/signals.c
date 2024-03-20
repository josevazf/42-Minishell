/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:59:35 by tiaferna          #+#    #+#             */
/*   Updated: 2024/03/20 18:17:34 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigpipe_handler(int signo)
{
	(void)signo;
	printf("Received SIGPIPE signal. Pipe closed by child process.\n");
	exit(EXIT_FAILURE);
}

void	sigint_hdhandler(int signo)
{
	if (signo == SIGINT)
	{
		g_signo = 130;
		write(1, "\n", 1);
		exit(g_signo);
	}
}

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_signo = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sighandler_fork(int signo)
{
	if (signo == SIGINT || signo == SIGQUIT)
		g_signo = 128 + signo;
}

void	set_signals(void)
{
	g_signo = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
