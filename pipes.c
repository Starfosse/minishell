#include "minishell.h"

void	creat_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_nbr - 1)
	{
		if (pipe(pipex->pipe + 2 * i) < 0)
			free_father(pipex);
		i++;
	}
}

void	free_father(t_pipex *pipex)
{
	/*int	i;

	i = 0;
	close(pipex->infile);
	close(pipex->outfile);
	while (pipex->cmd_path[i])
	{
		free(pipex->cmd_path[i]);
		i++;
	}
	free(pipex->cmd_path);*/
	free(pipex->pipe);
}

void	ft_init(t_pipex *pipex)
{
	int	j;
	t_cmd *tmp;

	j = 0;
	tmp = pipex->cmd;
	while(tmp != NULL)
	{
		j++;
		tmp = tmp->next;
	}
	pipex->pipe_on = 1;
	pipex->i = -1;
	pipex->cmd_nbr = j;
	pipex->pipe_nmbs = 2 * (pipex->cmd_nbr - 1);
	pipex->pipe = (int *)malloc(sizeof(int) * pipex->pipe_nmbs);
	creat_pipes(pipex);
	pipex->pipe_first = -2;
	pipex->pipe_second = 1;
	//g_status = -1;
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < (pipex->pipe_nmbs))
	{
		close(pipex->pipe[i]);
		i++;
	}
}