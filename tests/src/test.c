#include <stdio.h>
#include "test.h"

int	main(int argc, char **argv, char **envp)
{
	int i = -1;
	char **temp;
	char *var = NULL;
	char *content = NULL;
	int		nb_lines;
	
	i = 0;
	nb_lines = 0;
	while (envp[++i])
		nb_lines++;
	i = -1;
	while (++i < nb_lines) 
	{
		temp = ft_split(envp[i], '=');
		var = ft_strdup(temp[0]);
		content = ft_strdup(ft_strpbrk(envp[i], "=") + 1);
		printf("%s\t", var);
		printf("%s\n", content);
		ft_free_smatrix(temp);
		free(var);
		free(content);
	}
	(void)argc;
	(void)argv;
}