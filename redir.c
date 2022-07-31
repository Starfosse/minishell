#include "minishell.h"

void	remove_some_tabs(char **cmd, int count)
{
	int	i;
	
	i = 0;
	while (count > 0)
	{
		while((cmd[i][0] != '<' && cmd[i][0] != '>') && cmd[i])
			i++;
		while(cmd[i] && cmd[i + 2])
		{
			cmd[i] = NULL;
			cmd[i] = ft_strdup(cmd[i + 2]);
			i++;
		}
		cmd[i] = '\0';
		free(cmd[i]);
		free(cmd[i + 1]);
		count--;
	}
	
}

void	insert_outfile(t_cmd *cmd, int *count, int *i, int choice, int j)
{
	t_cmd *tmp;

	tmp = cmd;
	if(choice == 1)
	{
		tmp->outfile = open(tmp->full_cmd[j + 1], O_CREAT | O_RDWR | O_TRUNC, 0000644);
		tmp->out = 1;
		(*count)++;
		(*i)++;
	}
	else
	{
		tmp->outfile = open(tmp->full_cmd[j + 1], O_CREAT | O_RDWR | O_APPEND, 0644);
		tmp->out = 2;
		(*count)++;
		(*i) += 2; 
	}
}

int read_stdin(char *str)
{
    char *line;
    char  *buffer;
	int *p;

	p = (int *)malloc(sizeof(int) * 2);
	pipe(p);
    buffer = NULL;
	line = get_next_line(0);
    while(strncmp(str, line, (strlen(line) - 1))) // not good
	{
        buffer = ft_strjoin1(buffer, line);
		line = get_next_line(0);
	}
    ft_putstr_fd(buffer, p[1]);
    close(p[1]);
    return(p[0]);
}

void	insert_infile(t_cmd *cmd, int *count, int *i, int choice, int j)
{
	t_cmd *tmp;

	tmp = cmd;
	if(choice == 1)
	{
		tmp->infile = open(tmp->full_cmd[j + 1], O_RDONLY);
		tmp->in = 1;
		(*count)++;
		(*i)++;
	}
	else
	{
		tmp->infile = read_stdin(tmp->full_cmd[j + 1]);
		tmp->in = 2;
		(*count)++;
		(*i) += 2; 
	}
}

void	check_str(t_cmd *tmp, int i, int j, int *count)
{
	while(tmp->full_cmd[j] != NULL)
	{
		i = 0;
		while(tmp->full_cmd[j][i])
		{
			if(tmp->full_cmd[j][i] == '>' && tmp->full_cmd[j][i + 1] != '>')
				insert_outfile(tmp, count, &i, 1, j);
			else if(tmp->full_cmd[j][i] == '<' && tmp->full_cmd[j][i + 1] != '<')
				insert_infile(tmp, count, &i, 1, j);
			else if(tmp->full_cmd[j][i] == '>' && tmp->full_cmd[j][i + 1] == '>')
				insert_outfile(tmp, count, &i, 2, j);
			else if(tmp->full_cmd[j][i] == '<' && tmp->full_cmd[j][i + 1] == '<')
				insert_infile(tmp, count, &i, 2, j);
			else
				i++;
		}
		j++;
	}
}

void	check_redir(t_cmd *cmd)
{
	int	i;
	int j;
	int	count;
	t_cmd *tmp;

	i = 0;
	j = 0;
	tmp = cmd;
	count = 0;
	tmp->out = 0;
	tmp->in = 0;
	check_str(cmd, i, j, &count);
	remove_some_tabs(tmp->full_cmd, count);
	return;
}