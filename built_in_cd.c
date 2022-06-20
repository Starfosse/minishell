#include "minishell.h"

char    *get_var(char *str)
{
    int     i;
    int     j;
    char    *var;

    j = 0;
    i = 0;
    while(str[i] != '=')
        i++;
    var = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
    i++;
    while(str[i])
        var[j++] = str[i++];
    var[j] = '\0';
    return(var);
}

char    *ft_getenv(char *str, t_env **env)
{
    t_env *envi;
    envi = *env;
    while(envi)
    {
        if(!ft_strncmp(str, envi->var, ft_strlen(str)))
            return(get_var(envi->var));
        envi = envi->next;
    }
    return NULL;
}

void    change_pwd(char *path, int return_value, t_env **env)
{
    char cwd[PATH_MAX];
    char *OLDPWD;
    char *PWD;

    if (return_value == -1)
	{
		write(2, "cd: ", 4);
		write(2, path, ft_strlen(path));
		write(2, ": No such file or directory\n", 28);
	}
    else
    {
        getcwd(cwd, sizeof(cwd));
        OLDPWD = (char *) malloc (sizeof(char) * (ft_strlen(ft_getenv("PWD", env)) + 8));
        OLDPWD[ft_strlen(ft_getenv("PWD", env)) + 8] = '\0';
        OLDPWD = ft_strcpy(OLDPWD, "OLDPWD=");
        OLDPWD = ft_strcat(OLDPWD, ft_getenv("PWD", env));
        check_export(OLDPWD, env);
        PWD = (char *) malloc(sizeof(char) * ft_strlen(cwd) + 5);
        ft_strcpy(PWD, "PWD=");
        ft_strcat(PWD, cwd);
        PWD[ft_strlen(cwd) + 5] = '\0';
        check_export(PWD, env);
    }
}

int build_in_cd2(char *path, t_env **env, char *buffer)
{
    int return_value;
    char path2[PATH_MAX];
    char *last_slash;

    return_value = -1;
    if (strcmp(path, ".." ) == 0)
    {
        ft_strcpy(path2, ft_getenv("PWD", env));
        last_slash = ft_strrchr(path2, '/');
        *last_slash = '\0';
        return_value = chdir(path2);
    }
	else if (strcmp(path, "." ) == 0)
        return_value = chdir(ft_getenv("PWD", env));
	else if(path[0] != '/')
    {
        ft_strcpy(buffer, ft_getenv("PWD", env));
        ft_strcat(buffer, "/");
        ft_strcat(buffer, path);
        return_value = chdir(path);
    }
	else 
		return_value = chdir(path);
    return (return_value);
}

int	built_in_cd(char *path, t_env **env)
{
	int return_value;
    char buffer [PATH_MAX];

    return_value = -1;
	if (path == NULL || strcmp(path, "~" ) == 0)
		return_value = chdir(getenv("HOME"));
	else if (strcmp(path, "-" ) == 0)
	{
        return_value = chdir(ft_getenv("OLDPWD", env));
        ft_strcpy(buffer, ft_getenv("PWD", env));
		ft_putstr(buffer);
		write(1, "\n", 1);
	}
	else 
        return_value = build_in_cd2(path, env, buffer);
	change_pwd(path, return_value, env);
    return (EXIT_SUCCESS);
}