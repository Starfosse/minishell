#include "minishell.h"

int	ft_strlen2(char *str)
{
	int i = 0;
	int count = 0;
	if(str[i] == '$')
		i++;
	else
		return(0);
	while(str[i])
	{
		i++;
		count++;
	}
	return (count);
}

void	change_str(char *cmd, char *env)
{
	printf("cmd avant == %s\n", cmd);
	int size = ft_strlen(env);
	free(cmd);
	cmd = (char *) malloc (sizeof(char) * size + 1);
	ft_strcpy(cmd, env);
	printf("cmd aaprès1 == %s\n", cmd);
}

void	is_dollar(char **cmd, t_env **env)
{
	char **envi;
	int	i;
	int j;

	envi = lst_to_array(env);
	j = -1;
	while(cmd[++j])
	{
		i = -1;
		if(cmd[j][0] == '$')
		{
			while(envi[++i])
			{
				if(!ft_strncmp(envi[i], cmd[j] + 1, ft_strlen2(cmd[j])))
				{
					free(cmd[j]);
					cmd[j] = (char *) malloc (sizeof(char) * (ft_strlen(envi[i]) + 1));
					ft_strcpy(cmd[j], envi[i]);
					printf("cmd[j] == %s\n", cmd[j]);
					break;
				}
			}
		}
	}
}

t_cmd	*ft_lstnew2(void *content)
{
	t_cmd	*list;

	list = malloc(sizeof(t_cmd));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

void	ft_lstadd_back2(t_cmd **alst, t_cmd *new)
{
	t_cmd	*tmp;

	tmp = *alst;
	if (!new)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
}

char	*get_str(char *str, int i, int j)
{
	char *tmp;
	int count = 0;
	tmp = (char *) malloc (sizeof(char) * (i - j + 1));
	while(j < i)
	{
		tmp[count] = str[j];
		j++;
		count++;
	}
	tmp[count] = '\0';
	count = 0;
	while(tmp[count])
		count++;
	return(tmp);
}

int	is_pipe(char *buffer)
{
	int	i = 0;
	while(buffer[i])
	{
		if(buffer[i] == '|')
			return(1);
		i++;
	}
	return (0);
}