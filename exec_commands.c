#include "minishell.h"

void	exec_cmd(char **cmd, char **env)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	} 
	else 
	{
		if (execve(cmd[0], cmd, env) == -1)
		{
			//g_status = 126;
			perror("shell");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
}

void	free_array(char **array)
{
	int	i;

	i = -1;
	while(array[++i])
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}

char	*get_path(char **env)
{
	int	i;
	char	*path = NULL;

	i = -1;
	while(env[++i])
	{
		if (!strncmp(env[i], "PATH=", 5))
		{
			path = strdup(&env[i][5]);
			return (path);
		}
	}
	return (NULL);
}

void	insert_path(char **cmd, char *path)
{
	int 	i;
	char	*bin;
	char	**path_split;

	i = -1;
	bin = NULL;
	path_split = NULL;
	path_split = ft_split(path, ':');
	free(path);
	path = NULL;
	while(path_split[++i])
	{
		bin = (char *)malloc(sizeof(char) * (strlen(path_split[i]) + 1 + strlen(cmd[0]) + 1));
		if (bin == NULL)
			break ;
		strcat(bin, path_split[i]);
		strcat(bin, "/");
		strcat(bin, cmd[0]);
		if (access(bin, F_OK) == 0)
			break ;
		free(bin);
		bin = NULL;
	}
	free_array(path_split);
	free(cmd[0]);
	cmd[0] = bin;
}

void	get_absolute_path(char **cmd, char **env)
{
	char	*path = NULL;

	path = get_path(env);
	if (path == NULL)
		return ;
	if (cmd[0][0] != '/' && ft_strncmp(cmd[0], "./", 2) != 0) 
		insert_path(cmd, path);
    else 
    {
		free(path);
		path = NULL;
	}
}