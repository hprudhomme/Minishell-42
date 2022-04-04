# include "../include/minishell.h"

void ft_pwd(char **my_env)
{
    write(1, my_getenv(my_env, "PWD"), ft_strlen(getenv("PWD")));
    write(1, "\n", 1);
}