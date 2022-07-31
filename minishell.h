#ifndef MINISHELL_H
# define MINISHELL_H

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

# define PATH_MAX 2048

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
	int		infile;
	int		outfile;
	int 	in;
	int 	out;
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
	int print_exit;
}t_pipex;

size_t	ft_strlen1(char *str);
char	*ft_strjoin1(char *s1, char *s2);
char	*ft_strchr1(char *s, int c);
char	*get_next_line(int fd);
char	*get_read(int fd, char *save);
char	*get_line(char *save);
char	*get_save(char *save);
void	exec_cmd(char **cmd, char **env);
void	get_absolute_path(char **cmd, char **env);
int	exec_built_in(char **built_in, t_env **env, t_pipex *pipex);
int	    is_built_in(char *cmd);
char    *ft_check(char *buffer);
void	dup_env(char **envp, t_env **env);
char	**lst_to_array(t_env **env);
void	add_var_env(char *var, t_env **env);
int	built_in_pwd(void);
int	built_in_echo(char **path);
int	built_in_cd(char *path, t_env **env);
int 	check_export(char *var, t_env **env);
int    built_in_env(t_env **env);
int	built_in_unset(char *built_in, t_env **env);
int	built_in_export(char **built_in, t_env **env);
int	built_in_exit(t_pipex *pipex);
int	multiple_cmd(char *buffer, t_env **env);
void	close_pipes(t_pipex *pipex);
void	check_redir(t_cmd *cmd);
void	choose_files(int first, int second);
char	**lst_to_array();
int		prompt();
void	is_dollar(char **cmd, t_env **env);
int		is_pipe(char *buffer);
int	ft_son(t_cmd *cmd, t_pipex *pipex, t_env **env);
void	ft_lstadd_back2(t_cmd **alst, t_cmd *new);
void	free_father(t_pipex *pipex);
void	choose_redir(t_cmd *cmd, t_pipex pipex);
t_cmd	*ft_lstnew2(void *content);
char	*get_str(char *str, int i, int j);
void	ft_init(t_pipex *pipex);
void	run_cmd(t_cmd *cmd, t_pipex *pipex, t_env **env);
int	single_cmd(char *buffer, t_env **env);
void	choose_redir2(t_cmd *cmd);
void	exec_cmd(char **cmd, char **env);
void	select_files(t_cmd *cmd, t_pipex pipex);
void	select_files2(t_cmd *cmd, t_pipex pipex);
void	select_files3(t_cmd *cmd, t_pipex pipex);
void	select_files4(t_cmd *cmd);
char    *new_buffer(char *buffer, int count);
char    *ft_check(char *buffer);
char    *check_new_buffer(char *new_buffer, int count);
int 	next_single_quote(char *buffer, int i);
int 	next_quotes(char *buffer, int i);
int 	is_meta(char c);
void	create_fd(char *str);
void    sigint_handler(int status);
char	**custom_split(char *argv);
void	name_redir(t_cmd *cmd, t_env **env);
int	check_syntax(t_cmd *cmd);
void	free_array(char **array);
char	*get_path(char **env);
int	is_cmd(char	*str, t_env **env);
int	fork_store(pid_t *pid_res);

#endif