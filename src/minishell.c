/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patatoss <patatoss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:06:33 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/03 11:48:13 by patatoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

int		main(int argc, char **argv, char **envp)
{
	char 		*input;
	t_mshell	*init;
	
	if (argc != 1)
		args_error();
	input = readline("minishell$> ");
	if (ft_strlen(input) == 0)
	{
		free(input);
		ft_printf("Tente novamente\n");
		return (0);
	}
	quotes_checker(input); // coloquei esta verificacao logo apos a funcao readline para evitar avancar no programa caso o input tenha falta de quote(s) - Tiago
	init = (t_mshell *)malloc(sizeof(t_mshell));
	init->env_table = create_envll(envp, 0);
	lexer_main(init, input);
	export(init);
	// parser_main(init);
/* 	while (init->env_table)
	{
		printf("%s\t", init->env_table->var);
		printf("%s\n", init->env_table->content);
		init->env_table = init->env_table->next;
	} */
	free(input);
	delete_lists(init);
	free(init);
	(void)argv;
	return (0);
}
