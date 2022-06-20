#include "minishell.h"

void	run_cmd(t_cmd *cmd, t_pipex pipex, t_env **env)
{
	t_cmd *tmp;
	char **envi;

    tmp = cmd;
	envi = NULL;
    pipex.pid = fork();
	if (pipex.pid > 0)
	{
		waitpid(pipex.pid, &pipex.status, 0);
		kill(pipex.pid, SIGTERM);
	} 
	else if (!pipex.pid)
	{
		select_files4(tmp);
		if (tmp->full_cmd[0] == NULL)
			printf("Command not found\n");
		else if (is_built_in(tmp->full_cmd[0])) 
		{
			//envi = lst_to_array(env);
			exec_built_in(tmp->full_cmd, env);
		}
		else
		{
			envi = lst_to_array(env);
			get_absolute_path(tmp->full_cmd, envi);
			execve(tmp->full_cmd[0], tmp->full_cmd, envi);
		}
	}
}

void	single_cmd(char *buffer, t_env **env)
{
	t_pipex pipex;
    t_cmd *test1;
    
	pipex.cmd = NULL;
	pipex.cmd = ft_lstnew2((void *) buffer);
	test1 = pipex.cmd;
	test1->full_cmd = ft_split((char *)test1->content, ' ');
	check_redir(test1);
	is_dollar(test1->full_cmd, env);
	run_cmd(test1, pipex, env);
}