#include "minishell.h"

int is_meta(char c)
{
    int i;

    i = -1;
    char meta[] = {'A', 'b', 'B', 'd', 'D', 'f', 'n', 'r', 's', 'S', 't', 'v', 'w', 'W', 'z', 'Z', '-', '\0'};
    while(meta[++i])
        if(c == meta[i])
            return(1);
    return(0);
}

int next_quotes(char *buffer, int i)
{
    int count;

    count = 0;
    while(buffer[++i])
    {
        if(buffer[i] == '\"' && count > 1)
            return(1);
        else if (buffer[i] == '\"' && count == 0)
            return (0);
        count++;
    }
    return(0);
}

int next_single_quote(char *buffer, int i)
{
    int count;

    count = 0;
    while(buffer[++i])
    {
        if(buffer[i] == '\'' && count > 1)
            return(1);
        else if (buffer[i] == '\'' && count == 0)
            return(0);
        count++;
    }
    return(0);
}

char    *check_new_buffer(char *new_buffer, int count)
{
    char    *new_new_buffer;
    int     i;
    int     j;

    j = 0;
    i = 0;
    if(new_buffer[0] != ' ')
        return (new_buffer);
    while(new_buffer[i] == ' ')
        i++;
    new_new_buffer = (char *) malloc (sizeof(char) * count - i + 1);
    while(new_buffer[i])
    {
        new_new_buffer[j] = new_buffer[i];
        j++;
        i++;
    }
    new_new_buffer[j] = '\0';
    return (new_new_buffer);
}

