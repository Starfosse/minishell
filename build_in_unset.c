#include "minishell.h"

void	built_in_unset2(t_env **env, int count2)
{
	int	i;
	t_env *envi;

	envi = *env;
	i = 0;
	while (i < count2 - 1)
	{
		envi = envi->next;
		i++;
	}
	if (envi->next->next)
		envi->next = envi->next->next;
	else
		envi->next = NULL;
}

int	built_in_unset(char *built_in, t_env **env)
{
	t_env *envi;
	int	size;
	int count;
	int count2;

	count = 0;
	envi = *env;
	count2 = -1;
	while(envi != NULL)
	{
		size = 0;
		while(envi->var[size] != '=' && envi->var[size])
			size++;
		if (!ft_strncmp(envi->var, built_in, size))
			count2 = count;
		envi = envi->next;
		count++;
	}
	if(count2 == -1)
		return (EXIT_SUCCESS);
	built_in_unset2(env, count2);
	return (EXIT_SUCCESS);
}