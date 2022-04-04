# include "../include/minishell.h"

void    ft_env(char **my_env)
{
    int x;

    x = 0;
    while (my_env[x])
    {
        write(1, my_env[x], ft_strlen(my_env[x]));
        write(1, "\n", 1);
        x++;
    }
}