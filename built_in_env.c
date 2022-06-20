#include "minishell.h"

int	is_empty(char *var)
{
	int	i = 0;
	while(var[i] != '=' && var[i])
		i++;
	i++;
	if(var[i] == '\'' && var[i + 1] == '\'' && !var[i + 2])
		return(1);
	return(0);
}

int    built_in_env(t_env **env)
{
	t_env	*tmp;
	tmp = *env;
	while(tmp)
	{
		if (is_empty(tmp->var))
			tmp = tmp->next;
		else
		{	
			ft_putstr(tmp->var);
			write(1, "\n", 1);
			tmp = tmp->next;
		}
	}
	return (EXIT_SUCCESS);
}