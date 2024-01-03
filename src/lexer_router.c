/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_router.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patatoss <patatoss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 08:41:19 by tiaferna          #+#    #+#             */
/*   Updated: 2023/12/21 17:45:58 by patatoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	lexer_router(t_lexer *tokens)
{
	t_lexer	*head;

	head = tokens;
	while (tokens)
	{
		if (tokens->str == "|")
			tokens->operator = TYPE_PIPE;
		else if (tokens->str = ">")
			tokens->operator = TYPE_GREAT;
		else if (tokens->str = ">>")
			tokens->operator = TYPE_DOU_GREAT;
		else if (tokens->str = "<")
			tokens->operator = TYPE_LESS;
		else if (tokens->str = "<<")
			tokens->operator = TYPE_DOU_LESS;
		else
			tokens->operator = TYPE_CMD;
	}
}