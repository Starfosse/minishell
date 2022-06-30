#include "minishell.h"

int	ft_space(int c)
{
	if ((c >= 33 && c <= 35) || (c >= 37 && c <= 59)
		|| (c == 61) || (c >= 63 && c <= 126))
		return (1);
	return (0);
}

int	length_words(char *argv, int i)
{
	int	size;
	size = 0;
	while(ft_space(argv[i]) && argv[i])
	{
		i++;
		size++;
	}
	return (size);
}

int	count_words2(char *argv, int i)
{
	int	count;
	
	count = 0;
	if(argv[i] == '>' && argv[i + 1] != '>')
		count++;
	else if(argv[i] == '<' && argv[i + 1] != '<')
		count++;
	else if(argv[i] == '>' && argv[i + 1] == '>')
		count += 2;
	else if(argv[i] == '<' && argv[i + 1] == '<')
		count += 2;
	else if (argv[i] && (ft_space(argv[i])))
		count += length_words(argv, i);
	else if (argv[i] == '$' && argv[i])
	{
		count++;
		i++;
		count += length_words(argv, i);
	}
	return (count);
}

void	count_str_redir(char *argv, int *i, int *count)
{
	if(argv[*i] == '>' && argv[*i + 1] != '>')
	{	
		(*count)++;
		(*i)++;
	}	
	else if(argv[*i] == '<' && argv[*i + 1] != '<')
	{
		(*count)++;
		(*i)++;
	}
	else if(argv[*i] == '>' && argv[*i + 1] == '>')
	{
		(*count)++;
		(*i) += 2;
	}
	else if(argv[*i] == '<' && argv[*i + 1] == '<')
	{
		(*count)++;
		(*i) += 2;
	}
}

void	count_str_spdo(char *argv, int *i, int *count, int choice)
{
	if(choice == 1)
	{
		(*count)++;
		(*i) += length_words(argv, *i);
	}
	else if (choice == 2)
	{	
		(*count)++;
		(*i)++;
		(*i) += length_words(argv, *i);
	}
}

int	count_str(char *argv)
{
	int	count;
	int i;
	
	count = 0;
	i = 0;
	while(argv[i])
	{
		if(argv[i] == '>' && argv[i + 1] != '>')
			count_str_redir(argv, &i, &count);
		else if(argv[i] == '<' && argv[i + 1] != '<')
			count_str_redir(argv, &i, &count);
		else if(argv[i] == '>' && argv[i + 1] == '>')
			count_str_redir(argv, &i, &count);
		else if(argv[i] == '<' && argv[i + 1] == '<')
			count_str_redir(argv, &i, &count);
		else if (argv[i] && (ft_space(argv[i])))
			count_str_spdo(argv, &i, &count, 1);
		else if (argv[i] == '$' && argv[i])
			count_str_spdo(argv, &i, &count, 2);
		while(argv[i] == ' ' && argv[i])
			i++;
	}
	return (count);
}

char	**custom_split(char *argv)
{
	int		i;
	int		j;
	char	**split;
	int	count;
	int	x;

	x = 0;
	count = count_str(argv);
    printf("count == %d\n", count);
	split = (char**) malloc (sizeof(char *) * (count + 1));
	i = 0;
	while(argv[x])
	{
		j = 0;
		while(argv[x] == ' ' && argv[x])
			x++;
		count = count_words2(argv, x);
		split[i] = (char *) malloc (sizeof(char) * (count + 1));
		while(j < count)
			split[i][j++] = argv[x++];
		split[i][j] = '\0';
        i++;
	}
	split[i] = '\0';
    printf("i == %d\n", i);
	return (split);
}