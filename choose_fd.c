#include "minishell.h"

void	choose_files(int first, int second)
{
	dup2(first, 0);
	dup2(second, 1);
}

void	select_files(t_cmd *cmd, t_pipex pipex)
{
	t_cmd *tmp;
	tmp = cmd;
	if(tmp->in && tmp->out)
		choose_files(tmp->infile, tmp->outfile);
	else if(tmp->in)
		choose_files(tmp->infile, pipex.pipe[1]);
	else if(tmp->out)
		choose_files(0, tmp->outfile);
	else 
		choose_files(0, pipex.pipe[1]);
}

void	select_files2(t_cmd *cmd, t_pipex pipex)
{
	t_cmd *tmp;
	tmp = cmd;
	if(tmp->in&& tmp->out)
		choose_files(tmp->infile, tmp->outfile);
	else if(tmp->in)
		choose_files(tmp->infile, 1);
	else if(tmp->out)
		choose_files(pipex.pipe[pipex.pipe_first], tmp->outfile);
	else
		choose_files(pipex.pipe[pipex.pipe_first], 1);
}

void	select_files3(t_cmd *cmd, t_pipex pipex)
{
	t_cmd *tmp;
	tmp = cmd;
	/*if(tmp->in == 2)
		tmp*/
	if(tmp->in&& tmp->out)
		choose_files(tmp->infile, tmp->outfile);
	else if(tmp->in)
		choose_files(tmp->infile, pipex.pipe[pipex.pipe_second]);
	else if(tmp->out)
		choose_files(pipex.pipe[pipex.pipe_first], tmp->outfile);
	else
		choose_files(pipex.pipe[pipex.pipe_first], pipex.pipe[pipex.pipe_second]);
}

void	select_files4(t_cmd *cmd)
{
	t_cmd *tmp;
	tmp = cmd;
	if(tmp->out && tmp->in)
	{
		choose_files(tmp->infile, tmp->outfile);
	}
	else if(tmp->in)
	{
		choose_files(tmp->infile, 1);
	}
	else if(tmp->out)
	{
		choose_files(0, tmp->outfile);
	}
	else
		return ;
}