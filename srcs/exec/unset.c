#include "../../include/minishell.h"

char    **ft_unset(t_mem *mem, char *s)
{
    char **new;
    char **temp;
    int i;
    int j;


    if (!is_in_env(mem->my_env, s))
    {
        mem->exit_statue += 1;
        return mem->my_env;
    }
    i = 0;
    j = 0;
    new = (char **)malloc(sizeof(char *) * (tab_2d_len(mem->my_env)));
    if (!new)
        return mem->my_env;
    i = 0;
    while (mem->my_env[i])
    {
        temp = ft_split(mem->my_env[i], '=');
        if (strcmp(temp[0], s) == 0)
            i++;
        else
            new[j++] = ft_strdup(mem->my_env[i++]);
        free_tab_2d(temp);
    }
    new[j] = NULL;
    free_tab_2d(mem->my_env);
    return new;
}


char    **ft_unsets(t_mem *mem, char **args)
{
    int i;

    close(mem->fd_exit_statue[0]);
    mem->exit_statue = 0;
    i = 0;
    while (args[i])
    {
        if (strcmp(args[i], "unset") == 0)
            break ;
        i++;
    }
    i++;
    while (args[i])
    {
        mem->my_env = ft_unset(mem, args[i]);
        i++;
    }
    write(mem->fd_exit_statue[1], &mem->exit_statue, sizeof(mem->exit_statue));
    close(mem->fd_exit_statue[1]);
    return (mem->my_env);
}