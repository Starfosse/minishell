# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif


typedef struct		s_env
{
	char			*var;		// var name exemple : PATH
	struct s_env	*next;
}					t_env;

//t_env	*first;
int g_status;
// First elem dans la liste chainee
typedef struct s_cmd
{
	void	*content;
	char	**full_cmd;
	char	**env;
	int	infile;
	int	outfile;
	int in;
	int out;
	char	**type;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_pstat
{
	pid_t		pid;
	int			status;
}	t_pstat;

typedef struct s_pipex
{
	t_cmd	*cmd;
	t_env	*env;
	int		pid;
	int		i;
	int		pipe_first;
	int		pipe_second;
	int		pipe_nmbs;
	int		infile;
	int		outfile;
	int 	cmd_nbr;
	int		*pipe;
	char	*path;
	char	*env_path;
	char	**cmd_path;
	char	**cmd_args;
	char	*commande;
	int status;
	int exit_status;
	int	pipe_on;
}t_pipex;

static void	free_array(char **array)
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

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*tab;

	i = 0;
	len = strlen(s);
	tab = (char *) malloc (sizeof(char) * (len + 1));
	if (!tab)
		return (0);
	while (i < len)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;
	if (!s)
		return ;
	i = 0;
	while (s[i])
		ft_putchar_fd(s[i++], fd);
}

size_t	ft_strlen1(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr1(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen1(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = (char *) malloc ((ft_strlen1(s1) + ft_strlen1(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[ft_strlen1(s1) + ft_strlen1(s2)] = '\0';
	free(s1);
	return (str);
}

char	*get_read(int fd, char *save)
{
	char	*buffer;
	int		reader;

	reader = 1;
	buffer = (char *) malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!ft_strchr1(save, '\n') && reader != 0)
	{
		reader = read(fd, buffer, BUFFER_SIZE);
		if (reader == -1)
		{
			free(buffer);
			return (save);
		}
		buffer[reader] = '\0';
		save = ft_strjoin1(save, buffer);
	}
	free (buffer);
	return (save);
}

char	*get_line(char *save)
{
	int		i;
	char	*line;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	line = (char *) malloc (sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		line[i] = save[i];
		i++;
	}	
	line[i] = '\0';
	return (line);
}

char	*get_save(char *save)
{
	char	*save2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free (save);
		return (NULL);
	}
	save2 = (char *) malloc (sizeof(char) * (ft_strlen1(save) - i + 1));
	if (!save2)
		return (NULL);
	i++;
	while (save[i])
		save2[j++] = save[i++];
	save2[j] = '\0';
	free(save);
	return (save2);
}

char	*get_next_line(int fd)
{
	static char	*save[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	save[fd] = get_read(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = get_line(save[fd]);
	save[fd] = get_save(save[fd]);
	return (line);
}

int	is_in_charset(char c, char b)
{
	if (c == b)
		return (1);
	return (0);
}

int	count_words(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && is_in_charset(str[i], c))
			i++;
		if (str[i])
			count++;
		while (str[i] && !is_in_charset(str[i], c))
			i++;
	}
	return (count);
}

int	word_lenght(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && !is_in_charset(str[i], c))
	{
		i++;
		count++;
	}
	return (count);
}

int	ft_strndup(char **dest, char const *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	*dest = (char *)malloc(sizeof(char) * (n + 1));
	if (!*dest)
		return (0);
	while (i < n && src[i])
	{
		(*dest)[i] = src[i];
		i++;
	}
	while (i < n)
	{
		(*dest)[i] = '\0';
		i++;
	}
	(*dest)[i] = '\0';
	return (n);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		number_word;
	int		word_len;
	char	**tab;

	i = 0;
	j = -1;
	if (!s)
		return (NULL);
	number_word = count_words(s, c);
	tab = (char **)malloc(sizeof(char *) * (number_word + 1));
	if (!tab)
		return (NULL);
	while (++j < number_word)
	{
		while (s[i] && is_in_charset(s[i], c))
			i++;
		word_len = word_lenght(s + i, c);
		i += ft_strndup(&tab[j], s + i, word_len);
		if (!tab[j])
			return (NULL);
	}
	tab[j] = NULL;
	return (tab);
}


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

t_cmd	*ft_lstnew2(void *content)
{
	t_cmd	*list;

	list = malloc(sizeof(t_cmd));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
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
	split = (char**) malloc (sizeof(char *) * (count + 1));
	i = -1;
	while(argv[x])
	{
		j = 0;
		while(argv[x] == ' ' && argv[x])
			x++;
		count = count_words2(argv, x);
		split[++i] = (char *) malloc (sizeof(char) * (count + 1));
		while(j < count)
			split[i][j++] = argv[x++];
		split[i][j] = '\0';
	}
	split[i] = '\0';
	return (split);
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

char *ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	printf("je passe%d \n", i);
	while (dest[i] != '\0') {
		printf("je passe%d \n", i);
		i++;
	}
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

/*void	*ft_memalloc(size_t size)
{
	void	*tmp;

	tmp = malloc(size);
	if (tmp == NULL)
		return (NULL);
	ft_bzero(tmp, size);
	return (tmp);
}*/

int	is_cmd(char	*str, char **env)
{
	char	*str2;
	int 	i;
	char	*bin;
	char	**path_split;
	char	*path;

	path = get_path(env);
	str2 = strdup(str);
	printf("str2 == %s\n", str2);
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
		printf("%d\n", i);
		printf("path_split[i] == %s\n", path_split[i]);
		ft_strcat(bin, path_split[i]);
		printf("bin == %s\n", bin);
		strcat(bin, "/");
		strcat(bin, str2);
		printf("bin == %s\n", bin);
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

void	name_redir(t_cmd *cmd, char **env)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	i = 0;
	while(tmp->full_cmd[i])
		i++;
	tmp->type = (char **) malloc(sizeof(char*) * (i + 1));
	printf("629 == %d\n", i);
	i = -1;
	while(tmp->full_cmd[++i])
	{
		printf("PLOP == %d\n", i);
		if(tmp->full_cmd[i][0] == '<' || tmp->full_cmd[i][0] == '>')
			tmp->type[i] = ft_strdup("redir"); 
		else if(tmp->full_cmd[i][0] == '$')
			tmp->type[i] = ft_strdup("dollars");
		else if (is_cmd(tmp->full_cmd[i], env))
			tmp->type[i] = ft_strdup("cmd");
		else if(is_file(tmp->full_cmd[i]))
			tmp->type[i] = ft_strdup("file");
		else if(i >= 1)
			if(!strcmp(tmp->type[i - 1], "cmd"))
				tmp->type[i] = ft_strdup("arg");
		else
			tmp->type[i] = ft_strdup("other");
	}
	tmp->type[++i] = '\0'; 
}

void	tabs_less(char **cmd, int i)
{
	while(cmd[i] && cmd[i + 2])
	{
		cmd[i] = NULL;
		cmd[i] = ft_strdup(cmd[i + 2]);
		i++;
	}
	cmd[i] = '\0';
	free(cmd[i + 1]);
	free(cmd[i + 2]);
}

void	remove_some_tabs(char **cmd, int count)
{
	int	i;
	
	i = 0;
	while (count > 0)
	{
		while((cmd[i][0] != '<' && cmd[i][0] != '>') && cmd[i])
			i++;
		//tabs_less(cmd, i);
		while(cmd[i] && cmd[i + 2])
		{
			cmd[i] = NULL;
			cmd[i] = ft_strdup(cmd[i + 2]);
			i++;
		}
		cmd[i] = '\0';
		free(cmd[i + 1]);
		free(cmd[i + 2]);
		count--;
	}
	
}

void	check_syntax(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	i = 0;
	while(tmp->full_cmd[i])
	{
		if(tmp->type[i] == "redir" && tmp->type[i + 1] != "file" )
		{
			//(message erreur + arrêt fonction = "No Such file or directory");
			return;
		}
		if(tmp->type[i] == "redir" && !tmp->full_cmd[i])
		{
			//(message erreur + arrêt fonction = "syntax error near unexpected token 'newline'");
			return;
		}
	}
}

void	m(t_pipex *pipex)
{
	pipex->i = 7;
}

int main(int argc, char **argv, char **env)
{    
	if (!argc && !argv && !env)
		return(0);
	t_pipex pipex;
	m(&pipex);
	printf("pipex.i == %d\n", pipex.i);
    /*t_cmd *test1;
	pipex.cmd = NULL;
	pipex.cmd = ft_lstnew2((void *) argv[1]);
	test1 = pipex.cmd;
	test1->full_cmd = custom_split((char *)test1->content);*/
	//int i = 0;
	//remove_some_tabs(test1->full_cmd, 2);
	//name_redir(test1, env);
	//check_syntax(test1);
	/*while(test1->full_cmd[i])
	{
		printf("(après)test1->full_cmd[%d] == %s\n", i, test1->full_cmd[i]);
		//printf("test1->type[%d] == %s\n", i, test1->type[i]);
		i++;
	}*/
    return (0);
}