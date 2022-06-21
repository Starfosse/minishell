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

void	create_fd(char *str)
{
	int total = 0;
	char *buffer;
	buffer = NULL;
	char *test;
	char *test1;
	test = NULL;
	test = get_next_line(0);
	test1 = strndup(test, ft_strlen(test) - 1);
	while(strcmp(str, test1) != 0)
	{
		total = strcmp(str, test1);
		printf("total == %d\n", total);
		printf("str == [%s] et test == [%s]\n", str, test1);
		buffer = ft_strjoin1(buffer, test);
		printf("buffer == %s", buffer);
		free(test);
		test = get_next_line(0);
		test1 = strndup(test, ft_strlen(test) - 1);
	}
	printf("dépassé\n");
	return ;
}

int	ft_son(t_cmd *cmd, t_pipex pipex, t_env **env)
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
		if (pipex.i == 0)
			select_files(cmd, pipex);
		else if (pipex.i == pipex.cmd_nbr - 1)
		{
			//printf("tmp->str == %s\n", tmp->str);
			select_files2(cmd, pipex);
		}
		else
			select_files3(cmd, pipex);
		close_pipes(&pipex);
		/*if(tmp->in == 2)
		{
			printf("tmp->str == %s\n", tmp->str);
			create_fd(tmp->str);
		}*/
		if (is_built_in(tmp->full_cmd[0]))
		{
			exec_built_in(tmp->full_cmd, env);
			exit(EXIT_SUCCESS);
		}
		else
		{
			printf("tmp->str");
			envi = lst_to_array(env);
			printf("tmp->str");
			get_absolute_path(tmp->full_cmd, envi);
			printf("tmp->str");
			execve(tmp->full_cmd[0], tmp->full_cmd, envi);
			printf("tmp->str");
			exit(EXIT_SUCCESS);
		}
		exit(EXIT_FAILURE);
		//printf("pid == %d\n", pid);
	}
	//printf("test\n");
	//printf("pid == %d\n", pid);
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

void    check_list(t_cmd **cmd, t_env **env)
{
    t_cmd *test1;

	test1 = *cmd;
	while(test1 != NULL)
	{
		test1->full_cmd = ft_split((char *)test1->content, ' ');
		check_redir(test1);
		is_dollar(test1->full_cmd, env);
		test1 = test1->next;
	}
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
		//printf("pipe_status[%d].status == %d\n", i, pipe_status[i].status);
		++i;
	}
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

void	multiple_cmd(char *buffer, t_env **env)
{
	t_pipex pipex;
	t_pstat		*pipe_status;

	pipex.cmd = NULL;
    create_list(buffer, &pipex);
    check_list(&pipex.cmd, env);
	ft_init(&pipex);
	pipe_status = create_pipes_status(pipex.cmd_nbr);
	t_cmd *test2;
	test2 = pipex.cmd;
	while (++(pipex.i) < pipex.cmd_nbr)
	{
		pipe_status[pipex.i].pid = ft_son(test2, pipex, env);
		//printf("pipe_status[pipex.i].pid == %d\n", pipe_status[pipex.i].pid);
		pipex.pipe_first += 2;
		pipex.pipe_second += 2;
		test2 = test2->next;
	}
	close_pipes(&pipex);
	wait_all_pid(pipe_status, pipex.cmd_nbr);
	//waitpid(-1, NULL, 0);
}