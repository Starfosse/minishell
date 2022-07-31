#include "minishell.h"

void    sigint_handler(int status) 
{
    if (status == SIGQUIT)
    {
		printf("ne fait rien\n");
        //exit(0);
    }
    else if (status == SIGINT)
    {
        printf("\n"); // Move to a new line
        g_status = 130;
        rl_on_new_line(); // Regenerate the prompt on a newline
        rl_replace_line("", 0); // Clear the previous text
        rl_redisplay();
    }
    /*else if (status == ctrl-/)
    {
        ??;
    }*/
}