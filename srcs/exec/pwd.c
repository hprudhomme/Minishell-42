#include "../../include/minishell.h"

int  ft_pwd(char **my_env, t_mem *mem)
{
    char *pwd;

    pwd =  my_getenv(my_env, "PWD");
    write(1, pwd, ft_strlen(pwd));
    write(1, "\n", 1);
    mem->exit_statue = 0;
    free(pwd);
    return (1);
}
