#include "minishell.h"

char	**lst_to_array(t_env **env)
{
	char	**array = NULL;
	t_env	*tmp = *env;
	size_t	idx = 0;

	while (tmp) {
		idx++;
		tmp= tmp->next;
	}
	array = (char **)calloc(sizeof(char *), idx + 1);
	if (array == NULL) {
		perror("calloc");
		exit(-1);
	}
	tmp = *env;
	idx = 0;
	while (tmp) {
		array[idx] = tmp->var;
		tmp = tmp->next;
		idx++;
	}
	return (array);
}

char	*new_var3(char *var)
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

void	add_var_env(char *var, t_env **env)
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
	var2 = new_var3(var);
	new_var->var = var2;
	new_var->next = NULL;
	if (envi == NULL)
		*env = new_var;
	else 
	{
		while (envi->next != NULL)
			envi = envi->next;
		envi->next = new_var;
	}
}

void	dup_env(char **envp, t_env **env)
{
	int	i;

	i = 0;
	while(envp[i])
	{
		add_var_env(envp[i], env);
		i++;
	}
}