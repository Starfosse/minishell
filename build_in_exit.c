#include "minishell.h"

int	built_in_exit(t_pipex *pipex)
{
	pipex->print_exit = 1;
	printf("exit\n");
	pipex->print_exit = 1;
	//exit(0);
	return (EXIT_SUCCESS);
}