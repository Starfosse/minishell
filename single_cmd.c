#include "minishell.h"

void	run_cmd(t_cmd *cmd, t_pipex *pipex, t_env **env)
{
	t_cmd *tmp;
	char **envi;

    tmp = cmd;
	envi = NULL;
	pid_t pid;
	if (fork_store(&pid) == -1)
		return ;
	if (!pid)
	{
		select_files4(tmp);
		/*if (is_cmd(tmp->full_cmd[0], env))
		{
			g_status = 127;
			printf("Command not found\n");
		}*/
		if (is_built_in(tmp->full_cmd[0]))
		{
			exec_built_in(tmp->full_cmd, env, pipex);
			exit(EXIT_SUCCESS);
		}
		else
		{
			envi = lst_to_array(env);
			get_absolute_path(tmp->full_cmd, envi);
			execve(tmp->full_cmd[0], tmp->full_cmd, envi);
			exit(EXIT_SUCCESS);
		}
	}
	else
		if(!ft_strcmp(tmp->full_cmd[0], "exit"))
			pipex->print_exit = 1;
}

int	single_cmd(char *buffer, t_env **env)
{
	t_pipex pipex;
    t_cmd *test1;
    
	pipex.cmd = NULL;
	pipex.cmd = ft_lstnew2((void *) buffer);
	pipex.print_exit = 0;
	test1 = pipex.cmd;
	test1->full_cmd = custom_split(test1->content);
	name_redir(test1, env);
	if(!check_syntax(test1))
		return (0);
	check_redir(test1);
	is_dollar(test1->full_cmd, env);
	run_cmd(test1, &pipex, env);
	waitpid(-1, NULL, 0);
	printf("pipex.print_exit == %d\n", pipex.print_exit);
	if(pipex.print_exit == 1)
		return(1);
	return(0);
}