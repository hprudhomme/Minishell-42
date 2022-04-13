#include "../../include/minishell.h"

int    ft_env(char **my_env, t_mem *mem)
{
    int x;

    x = 0;
    while (my_env[x])
    {
        write(1, my_env[x], ft_strlen(my_env[x]));
        write(1, "\n", 1);
        x++;
    }
    mem->exit_statue = 0;
    return (1);
}
