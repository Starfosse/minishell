#include "minishell.h"

int	is_built_in(char *cmd)
{
	if (!strcmp(cmd, "pwd"))
		return (1);
	else if (!strcmp(cmd, "cd"))
		return (1);
	else if (!strcmp(cmd, "echo"))
		return (1);
	else if(!strcmp(cmd, "env"))
		return (1);
	else if(!strcmp(cmd, "export"))
		return (1);
	else if(!strcmp(cmd, "exit"))
		return (1);
	else if(!strcmp(cmd, "unset"))
		return (1);
	return (0);
}

int	exec_built_in(char **built_in, t_env **env, t_pipex *pipex)
{
	if (!strcmp(built_in[0], "pwd"))
		return (built_in_pwd());
	else if (!strcmp(built_in[0], "cd"))
		return (built_in_cd(built_in[1], env));
	else if (!strcmp(built_in[0], "echo"))
		return (built_in_echo(built_in));
	else if(!strcmp(built_in[0], "env"))
		return (built_in_env(env));
	else if(!strcmp(built_in[0], "export"))
		return (built_in_export(built_in, env));
	else if(!strcmp(built_in[0], "exit"))
		return (built_in_exit(pipex));
	else if(!strcmp(built_in[0], "unset"))
		return (built_in_unset(built_in[1], env));
	printf("pipex.print_exit3 == %d\n", pipex->print_exit);
	return (1);
}
