#include "../../include/minishell.h"

int     is_egal(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] == '=')
            return 1;
        i++;
    }
    return 0;
}

char    **ft_export(t_mem *mem, char *s)
{
    char **new;
    char **temp;
    int i;

    i = 0;
    if (!is_egal(s))
        return mem->my_env;
    temp = ft_split(s, '=');
    if (is_in_env(mem->my_env, temp[0]))
        mem->my_env = ft_unset(mem, temp[0]);
    free_tab_2d(temp);
    new = (char **)malloc(sizeof(char *) * (tab_2d_len(mem->my_env) + 2));
    if (!new)
        return NULL;
    while (mem->my_env[i])
    {
        new[i] = ft_strdup(mem->my_env[i]);
        i++;
    }
    new[i] = ft_strdup(s);
    i++;
    new[i] = NULL;
    free_tab_2d(mem->my_env);
    return new;
}

char    **ft_exports(t_mem *mem, char **args)
{
    int i;

    close(mem->fd_exit_statue[0]);
    i = 0;
    while (args[i])
    {
        if (strcmp(args[i], "export") == 0)
            break ;
        i++;
    }
    i++;
    while (args[i])
    {
        mem->my_env = ft_export(mem, args[i]);
        i++;
    }
    mem->exit_statue = 0;
    write(mem->fd_exit_statue[1], &mem->exit_statue, sizeof(mem->exit_statue));
    close(mem->fd_exit_statue[1]);
    return (mem->my_env);
}
