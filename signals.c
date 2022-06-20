#include "minishell.h"

/*void    handler(int status) 
{
    if (status == SIGINT)
    {
        printf("gg\n");
        printf("\n"); // Move to a new line
        g_status = 130;
        rl_on_new_line(); // Regenerate the prompt on a newline
        rl_replace_line("", 0); // Clear the previous text
        rl_redisplay();
    }
    else if (status == SIQUIT)
    {
        //kill le process en cours;
    }
    else if (status == ctrl-d)
    {
        //kill le programme en cours;
    }
}*/

/*void	cancel_c2(int sig)
{
	(void) sig;
}

void	cancel_delimiters(t_m *mini, int i)
{
	static t_m	*m;

	if (!m)
		m = mini;
	if (i >= 2)
	{
		m->exit_status = 128 + i;
		m->signal_save(i);
	}
	else if (i == -100)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		m->exit_status = 130;
	}
	else
	{
		m->exit_status = 130;
		m->canceldelimiters = i;
	}
}

void	cancel_c(int sig)
{
	if (sig == SIGINT)
	{
		cancel_delimiters(NULL, -100);
	}
}

void	cancel_c3(int sig)
{
	if (sig == SIGINT)
	{
		cancel_delimiters(NULL, 1);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		close(0);
	}
}

void	cancel_c4(int sig)
{
	(void) sig;
	write(1, "\n", 1);
}

void	setup_signal(t_m *mini)
{
	mini->end = -1;
	mini->signal_save = signal(SIGINT, cancel_c);
	mini->cancel_c = cancel_c;
	mini->cancel_c2 = cancel_c2;
	mini->cancel_c4 = cancel_c4;
	signal(SIGQUIT, cancel_c2);
	cancel_delimiters(mini, 0);
}*/