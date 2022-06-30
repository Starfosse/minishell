#include "minishell.h"

int	is_cmd(char	*str, t_env **env)
{
	char	*str2;
	int 	i;
	char	*bin;
	char	**path_split;
	char	*path;
    char **envi;

    envi = lst_to_array(env);
	path = get_path(envi);
	str2 = strdup(str);
	i = -1;
	bin = NULL;
	path_split = NULL;
	path_split = ft_split(path, ':');
	free(path);
	path = NULL;
	while(path_split[++i])
	{
		bin = (char *)malloc(sizeof(char) * (strlen(path_split[i]) + 1 + strlen(str2) + 1));
		bzero(bin, sizeof((strlen(path_split[i]) + 1 + strlen(str2) + 1)));
		if (bin == NULL)
			break ;
		ft_strcat(bin, path_split[i]);
		strcat(bin, "/");
		strcat(bin, str2);
		if (access(bin, F_OK) == 0)
			return(1);
		free(bin);
		bin = NULL;
	}
	free_array(path_split);
	free(str2);
	return(0);
}

int	is_file(char *str)
{
	if (access(str, F_OK | W_OK | R_OK | X_OK) == 0)
		return (1);
	return (0);
}

void	name_redir(t_cmd *cmd, t_env **env)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	i = 0;
	while(tmp->full_cmd[i])
		i++;
	tmp->type = (char **) malloc(sizeof(char*) * (i + 1));
	i = -1;
	while(tmp->full_cmd[++i])
	{
        if(tmp->full_cmd[i][0] == '<' && tmp->full_cmd[i][1] == '<')
			tmp->type[i] = ft_strdup("heredoc"); 
		else if(tmp->full_cmd[i][0] == '<' || tmp->full_cmd[i][0] == '>')
			tmp->type[i] = ft_strdup("redir"); 
		else if(tmp->full_cmd[i][0] == '$')
			tmp->type[i] = ft_strdup("dollars");
		else if (is_cmd(tmp->full_cmd[i], env))
			tmp->type[i] = ft_strdup("cmd");
		else if(is_file(tmp->full_cmd[i]))
			tmp->type[i] = ft_strdup("file");
		else if(i >= 1)
        {
			if(!strcmp(tmp->type[i - 1], "cmd"))
				tmp->type[i] = ft_strdup("arg");
        }
		else
			tmp->type[i] = ft_strdup("other");
	}
	tmp->type[++i] = '\0'; 
}

int	check_syntax(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	i = 0;
	/*while(tmp->full_cmd[i])
	{
		printf("tmp->full_cmd[i] %s\n",tmp->full_cmd[i]);
		i++;
	}
	i = 0;*/
	int total = 0;
	while(tmp->full_cmd[i])
	{
		printf("tmp->full_cmd[%d] == %s et tmp->type == %s\n", i, tmp->full_cmd[i], tmp->type[i]);
		printf("tmp->full_cmd[%d + 1] == %s\n", i, tmp->full_cmd[i + 1]);
		total = ft_strcmp(tmp->type[i], "redir");
		printf("total == %d\n", total);
		if(!ft_strcmp(tmp->type[i], "redir") && ft_strcmp(tmp->type[i + 1], "file"))
		{
			printf("là\n");
            ft_putstr("No Such file or directory");
			return (0);
		}
		if(!ft_strcmp(tmp->type[i], "redir") && !tmp->full_cmd[i + 1])
		{
			printf("là\n");
            ft_putstr("syntax error near unexpected token 'newline'");
			return (0);
		}
        i++;
	}
	printf("zzzz\n");
	/*i++;
	if(!ft_strcmp(tmp->type[i], "redir") && !tmp->full_cmd[i + 1])
	{
		printf("là\n");
        ft_putstr("syntax error near unexpected token 'newline'");
		return (0);
	}*/
    return (1);
}