#include "minishell.h"

void    slash2(char *buffer, char *new_buffer, int *i, int *count)
{
    if (buffer[*i] == '\\' && is_meta(buffer[*i + 1]) )
            (*i) += 2;
    else if (buffer[*i] == '\\' && !is_meta(buffer[*i + 1]))
    {
        (*i)++;
        new_buffer[*count] = buffer[*i];
        (*i)++;
        (*count)++;
    }
}

void    quote2(char *buffer, char *new_buffer, int *i, int *count)
{
    if (buffer[*i] == '\'' && next_single_quote(buffer, *i))
    {
        (*i)++;
        while(buffer[*i] != '\'')
        {
            new_buffer[*count] = buffer[*i];
            (*i)++;
            (*count)++;
        }
        (*i)++;
    }
    else if (buffer[*i] == '\'' && !next_single_quote(buffer, *i))
        (*i) += 1;
}


void    double_quote2(char *buffer, char *new_buffer, int *i, int *count)
{
    int stop;

    stop = 0;
    if (buffer[*i] == '\"' && next_quotes(buffer, *i))
    {
        (*i)++;
        while(buffer[*i] != '\"')
        {
            if(buffer[*i] == '$')
                stop = 1;
            if(stop == 0)
            {
                new_buffer[*count] = buffer[*i];
                (*count)++;
                (*i)++;
            }
            else 
                (*i)++;
        }
        (*i)++;
    }
    else if (buffer[*i] == '\"' && !next_quotes(buffer, *i))
        (*i) += 1;
}

char    *run_new_buffer(char *buffer, char *new_buffer, int i, int count)
{
    while(buffer[i])
    {
        if (buffer[i] == '\\')
            slash2(buffer, new_buffer, &i, &count);
        else if (buffer[i] == '\'')
            quote2(buffer, new_buffer, & i, &count);
        else if (buffer[i] == '\"')
            double_quote2(buffer, new_buffer, &i, &count);
        while (buffer[i] != '\"' && buffer[i] != '\'' && buffer[i] != '\\' && buffer[i])
        {
            new_buffer[count] = buffer[i];
            i++;
            count++;
        }
    }
    new_buffer[count] = '\0';
    return (check_new_buffer(new_buffer, count));
}

char    *new_buffer(char *buffer, int count)
{
    char    *new_buffer;
    int i;

    new_buffer = (char *) malloc (sizeof(char) * count + 1);
    count = 0;
    i = 0;
    return(run_new_buffer(buffer, new_buffer, i, count));
}