#include "minishell.h"

int	fork_store(pid_t *pid_res)
{
	pid_t	pid;

	pid = fork();
	*pid_res = pid;
	if (pid == -1)
		return (-1);
	return (0);
}

int	ft_son(t_cmd *cmd, t_pipex *pipex, t_env **env)
{
	t_cmd *tmp;
    char **envi;
	tmp = cmd;
	envi = NULL;
	pid_t pid;
	//pipex.pid = fork();
	if (fork_store(&pid) == -1)
		return (1);
	if (pid == 0)
	{
		if (pipex->i == 0)
			select_files(cmd, *pipex);
		else if (pipex->i == pipex->cmd_nbr - 1)
			select_files2(cmd, *pipex);
		else
			select_files3(cmd, *pipex);
		close_pipes(pipex);
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
		exit(EXIT_FAILURE);
	}
	else
		if(!ft_strcmp(tmp->full_cmd[0], "exit"))
			pipex->print_exit = 1;
	return (pid);
}

void    create_list(char *buffer, t_pipex *pipex)
{
    t_cmd *tmp;
	int i;
	int j;

    i = 0;
	j = 0;
	tmp = NULL;
    while(buffer[i])
	{
		i++;
		if(buffer[i] == '|' || !buffer[i])
		{
			tmp = ft_lstnew2((void *) get_str(buffer, i, j));
			ft_lstadd_back2(&pipex->cmd, tmp);
			if(buffer[i] == '|')
				i++;
			j = i;
		}
	}
}

int    check_list(t_cmd **cmd, t_env **env)
{
    t_cmd *test1;
	test1 = *cmd;

	while(test1 != NULL)
	{
		test1->full_cmd = custom_split(test1->content);
		name_redir(test1, env);
		/*if(!check_syntax(test1))
			return(0);*/
		check_redir(test1);
		is_dollar(test1->full_cmd, env);
		test1 = test1->next;
	}
	return(1);
}

int	wait_all_pid(t_pstat *pipe_status, int size)
{
	int	i;
	int	status;

	i = 0;
	if (!pipe_status)
		return (1);
	while (i < size)
	{
		if (&pipe_status[i] != NULL && pipe_status[i].pid > 0)
		{
			waitpid(pipe_status[i].pid, &status, 0);
			if (WIFEXITED(status))
				pipe_status[i].status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				pipe_status[i].status = 128 + WTERMSIG(status);
			else if (WIFSTOPPED(status))
				pipe_status[i].status = 128 + WSTOPSIG(status);
			else if (WIFCONTINUED(status))
				pipe_status[i].status = 128 + WIFCONTINUED(status);
		}
		++i;
	}
	g_status = pipe_status[i].status;
	return (1);
}

t_pstat	*create_pipes_status(int pipe_size)
{
	t_pstat		*pipe_status;
	int			i;

	pipe_status = malloc(sizeof(t_pstat) * pipe_size);
	if (!pipe_status)
		return (NULL);
	i = -1;
	while (++i < pipe_size)
	{
		pipe_status[i].pid = 0;
		pipe_status[i].status = 0;
	}
	return (pipe_status);
}

int	multiple_cmd(char *buffer, t_env **env)
{
	t_pipex pipex;
	t_pstat		*pipe_status;

	pipex.cmd = NULL;
    create_list(buffer, &pipex);
	ft_init(&pipex);
    if(!check_list(&pipex.cmd, env))
		return (0);
	pipe_status = create_pipes_status(pipex.cmd_nbr);
	t_cmd *test2;
	test2 = pipex.cmd;
	while (++(pipex.i) < pipex.cmd_nbr)
	{
		pipe_status[pipex.i].pid = ft_son(test2, &pipex, env);
		//printf("pipe_status[pipex.i].pid == %d\n", pipe_status[pipex.i].pid);
		pipex.pipe_first += 2;
		pipex.pipe_second += 2;
		test2 = test2->next;
	}
	close_pipes(&pipex);
	wait_all_pid(pipe_status, pipex.cmd_nbr);
	if(pipex.print_exit == 1)
		return(1);
	return(0);
	//waitpid(-1, NULL, 0);
}