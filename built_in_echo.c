#include "minishell.h"

int	built_in_echo(char **path)
{
	int	i;
	int count = 0;
	while (path[count])
		count++;
	
	i = 0;
	if(path[1][0] == '-' && path[1][1] == 'n')
	{
		i = 1;
		while(path[++i])
			ft_putstr(path[i]);
	}
	else
	{
		while(path[++i])
		{
			ft_putstr(path[i]);
			if(count != i )
				ft_putstr(" ");
		}
		write(1, "\n", 1);
	}
	return (EXIT_SUCCESS);
}