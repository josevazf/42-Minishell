/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:06:33 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/12/18 18:47:21 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	***parse_env(char **envp)
{
	int		i;
	int		nb_lines;
	char	***env_list;
	
	i = 0;
	nb_lines = 0;
	while (envp[++i])
		nb_lines++;
	i = -1;
	env_list = (char ***)malloc(sizeof(char **) * nb_lines);
	while (++i < nb_lines)
		env_list[i] = (char **)malloc(sizeof(char *) * 3);
	i = -1;
	while (++i < nb_lines) 
	{
		env_list[i] = ft_split(envp[i], '=');
		ft_printf("%s\t", env_list[i][0]);
		ft_printf("%s\n", env_list[i][1]);
	}
	return (env_list);
}

int		main(int argc, char **argv, char **envp)
{
	char 		*input;
	t_mshell	*init;
	
	if (argc != 1)
		args_error();
	init = (t_mshell *)malloc(sizeof(t_mshell));
	init->env_table = parse_env(envp);
	input = readline("minishell$> ");
	lexer_main(input, envp);
	(void)argv;
	(void)envp;
	return (0);
}
