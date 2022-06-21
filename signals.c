#include "minishell.h"

void    handler(int status) 
{
    if (status == SIGINT)
    {
        //printf("gg\n");
        printf("\n"); // Move to a new line
        g_status = 130;
        rl_on_new_line(); // Regenerate the prompt on a newline
        rl_replace_line("", 0); // Clear the previous text
        rl_redisplay();
    }
    else if (status == SIGQUIT)
    {
		printf("exit\n");
        exit(0);
    }
    /*else if (status == ctrl-/)
    {
        ??;
    }*/
}
code 1


code 2

code 3