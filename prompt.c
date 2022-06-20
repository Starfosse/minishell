#include "minishell.h"

int	prompt(t_env **env)
{
	char	*buffer;
	buffer = (char *)calloc(sizeof(char), 2048);
	
	if (buffer == NULL) 
	{
		perror("Malloc failure");
		return (EXIT_FAILURE);
	}
	while ((buffer = readline("$>")))
	{
		buffer = ft_check(buffer);
		add_history(buffer);
		if(is_pipe(buffer))
			multiple_cmd(buffer, env);
		else
			single_cmd(buffer, env);
	}
	return(0);
}