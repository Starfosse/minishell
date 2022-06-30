#include "minishell.h"

int	built_in_exit(void)
{
	printf("exit\n");
	exit(0);
	return (EXIT_SUCCESS);
}