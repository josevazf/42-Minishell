/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patatoss <patatoss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:34:48 by patatoss          #+#    #+#             */
/*   Updated: 2023/12/21 11:40:47 by patatoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	delete_list_lexer(t_mshell *init)
{
	t_lexer	*temp;

	while (init->lexer)
	{
		temp = init->lexer;
		free(init->lexer->str);
		init->lexer->operator = 0;
		init->lexer->i = 0;
		init->lexer->prev = NULL;
		init->lexer = init->lexer->next;
		free(temp);
	}
}
