#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	if (ac == 0 || !av[0])
		return (0);
	t_env	*env;
	env = NULL;
	dup_env(envp, &env);
	/*t_env *tmp;
	tmp = env;
	while(tmp != NULL)
	{
		printf("tmp->var == %s\n", tmp->var);
		tmp = tmp->next;
	}*/
	/*struct sigaction sa;
    sa.sa_handler = &handler;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);*/
	signal(SIGQUIT, sigint_handler);
	signal(SIGINT, sigint_handler);
	prompt(&env);
	return(0);
}