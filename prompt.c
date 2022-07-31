#include "minishell.h"

int	prompt(t_env **env)
{
	char	*buffer;
	buffer = (char *)calloc(sizeof(char), 2048);
	ft_bzero(buffer, sizeof(char) * 2048);
	if (buffer == NULL) 
	{
		perror("Malloc failure");
		return (EXIT_FAILURE);
	}
	while ((buffer = readline("\e[0;35mMini\e[0;33mshell $>\e[0;37m ")) && isatty(0))
	{
		buffer = ft_check(buffer);
		add_history(buffer);
		if(is_pipe(buffer))
		{
			if (multiple_cmd(buffer, env))
			{
				//printf("aïe2\n");
				break;
			}
		}
		else
			if(single_cmd(buffer, env))
			{
				//printf("aïe1\n");
				break;
			}
	}
	if (buffer == NULL)
			printf("exit\n");
	return(0);
}