/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 07:57:15 by tiaferna          #+#    #+#             */
/*   Updated: 2023/12/08 14:46:03 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	echo(t_lexer lexer)
{
	while (lexer->next)
	{
		lexer = lexer->next;
		ft_printf("%s", lexer->input);
		if (lexer->next)
			ft_printf(" ");
	}
	return ;
}
