#include "minishell.h"

char	**sort_ascii(char **envp)
{
	int	count;
	int	i;
	int	j;
	char *tmp;
	char **tab;

	i = -1;
	count = 0;
	while (envp[count])
		count++;
	tab = (char **)malloc (sizeof(char *) * count + 1);
	while (++i < count)
	{
		j = i;
		while(++j < count)
			if (ft_strcmp(envp[i], envp[j]) > 0)
			{
				tmp = envp[i]; 
            	envp[i] = envp[j]; 
            	envp[j] = tmp; 
			}
		tab[i] = envp[i];
	}
	tab[i] = '\0';
	return (tab);
}

int check_export(char *var, t_env **env)
{
	t_env	*envi;
	int	count;

	count = 0;
	envi = *env;
	while(var[count] != '=' && var[count])
		count++;
	if(!var[count])
		return (0);
	while(envi)
	{
		if(!ft_strncmp(var, envi->var, count))
		{
			//printf("enviiiii->var == %s\n", envi->var);
			//free(envi->var);
			//printf("enviiiii->var == %s\n", envi->var);
			envi->var = (char *) malloc (sizeof(char) * ft_strlen(var) + 1);
			//printf("enviiiii->var == %s\n", envi->var);
			ft_strcpy(envi->var, var);
			//printf("enviiiii->var == %s\n", envi->var);
			return(1);
		}
		//printf("envi->var == %s\n", envi->var);
		envi = envi->next;
	}
	return(0);
}

char	*new_var2(char *var)
{
	int	i;
	int	j;
	char	*var2;

	i = 0;
	j = 0;
	if (!ft_strchr(var, '='))
	{
		var2 = (char *) malloc (sizeof(char) * (ft_strlen(var) + 4));
		while(var[i])
			var2[j++] = var[i++];
		var2[j++] = '=';
		var2[j++] = '\'';
		var2[j++] = '\'';
		var2[(ft_strlen(var) + 4)] = '\0';
	}
	else
	{
		var2 = (char *) malloc (sizeof(char) * (ft_strlen(var) + 2));
		while(var[i])
			var2[j++] = var[i++];
		var2[j] = '\0';
	}
	return(var2);
}

void	add_var_env2(char *var, t_env **env)
{
	t_env	*envi;
	t_env	*new_var;

	envi = *env;
	new_var = (t_env *)malloc(sizeof(t_env) * 1);
	char *var2;
	if (new_var == NULL) 
	{
		printf("Alloc failure\n");
		return ;
	}
	var2 = new_var2(var);
	new_var->var = var2;
	new_var->next = NULL;
	if (envi == NULL)
		envi = new_var;
	else 
	{
		while (envi->next != NULL)
			envi = envi->next;
		envi->next = new_var;
	}
}

int	built_in_export(char **built_in, t_env **env)
{
	int	i;
	char **tab;
	char **envi;

	envi = lst_to_array(env);
	i = -1;
	if(!built_in[1])
	{
		tab = sort_ascii(envi);
		while (tab[++i])
		{
			ft_putstr(tab[i]);
			ft_putstr("\n");
		}
		free(tab);
	}
	else
	{
		if(!check_export(built_in[1], env))
			add_var_env2(built_in[1], env);
	}
	return (EXIT_SUCCESS);
}