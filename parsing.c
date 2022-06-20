#include "minishell.h"

void    slash(char *buffer, int *i, int *count)
{
    if (buffer[*i] == '\\' && is_meta(buffer[*i + 1]))
            (*i) += 2;
    else if (buffer[*i] == '\\' && !is_meta(buffer[*i + 1]))
    {
        (*i) += 2;
        (*count) += 1;
    }
}

void    quote(char *buffer, int *i, int *count)
{
    if (buffer[*i] == '\'' && next_single_quote(buffer, *i))
    {
        (*i)++;
        while(buffer[*i] != '\'')
        {
            (*i)++;
            (*count)++;
        }
        (*i)++;
    }
    else if (buffer[*i] == '\'' && !next_single_quote(buffer, *i))
        (*i) += 1;
}

void    double_quote(char *buffer, int *i, int *count)
{
    int stop;

    stop = 0;
    if (buffer[*i] == '\"' && next_quotes(buffer, *i))
    {
        while(buffer[*i] != '\"')
        {
            if(buffer[*i] == '$')
                stop = 1;
            if(stop == 0)
            {
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

/*char    *run_check(char *buffer, int i, int count, int stop)
{
    while(buffer[i])
    {
        stop = 0;
        if (buffer[i] == '\\')
            slash(buffer, &i, &count)
        else if (buffer[i] == '\'')
            quote(buffer, &i, &count);
        else if (buffer[i] == '\"' && next_quotes(buffer, i))
            double_quote(buffer, &i, &count);
        while (buffer[i] != '\"' && buffer[i] != '\'' && buffer[i] != '\\' && buffer[i])
        {
            i++;
            count++;
        }
    }
    return(new_buffer(buffer, count));
}*/

char    *ft_check(char *buffer)
{
    int i;
    int count;

    count = 0;
    i = 0;
    while(buffer[i])
    {
        if (buffer[i] == '\\')
            slash(buffer, &i, &count);
        else if (buffer[i] == '\'')
            quote(buffer, &i, &count);
        else if (buffer[i] == '\"')
            double_quote(buffer, &i, &count);
        while (buffer[i] != '\"' && buffer[i] != '\'' && buffer[i] != '\\' && buffer[i])
        {
            i++;
            count++;
        }
    }
    return(new_buffer(buffer, count));
}