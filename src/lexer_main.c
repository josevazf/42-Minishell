/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patatoss <patatoss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 07:52:03 by tiaferna          #+#    #+#             */
/*   Updated: 2023/12/21 19:21:26 by patatoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

t_lexer	*lexer_list(char **args)
{
	int		i;
	int		j;
	t_lexer *lexer_list;
	t_lexer *head;

	i = 0;
	lexer_list = (t_lexer *)malloc(sizeof(t_lexer));
	head = lexer_list;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
			j++;
		lexer_list->str = (char *)malloc(sizeof(char) * j + 1);
		lexer_list->str[j] = '\0';
		while (--j >= 0)
			lexer_list->str[j] = args[i][j];
		lexer_list->next = NULL;
		if (args[++i])
		{
			lexer_list->next = (t_lexer *)malloc(sizeof(t_lexer));
			lexer_list = lexer_list->next;
		}
	}
	return (head);
}
	
int lexer_main(t_mshell *init, char *input, char **envp)
{
	char		**args;

	args = lexer_split(input);
	init->lexer = lexer_list(args);
	expander(init, envp);
	ft_free_smatrix(args);
	(void)envp;
	// TEST START
	while (init->lexer)
	{
		// find_cmd(init->lexer, envp);
		ft_printf("%s\n", init->lexer->str);
		init->lexer = init->lexer->next;
	}
	// TEST END
	return (0);
}
