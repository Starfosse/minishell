#include "minishell.h"

int	built_in_pwd(void)
{
	char	*cwd = NULL;

	cwd = (char *)malloc(sizeof(char) * (PATH_MAX + strlen("PWD=") + 1));
	if (cwd == NULL)
		return (EXIT_FAILURE);
	strcat(cwd, "PWD=");
	if (getcwd(&cwd[4], PATH_MAX) == NULL)
	{
		perror("getcwd()");
		return (EXIT_FAILURE);
	}
	ft_putstr(cwd);
	ft_putchar('\n');
	return (EXIT_SUCCESS);
}