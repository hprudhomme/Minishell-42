#include "../../include/minishell.h"

int  ft_pwd(char **my_env, t_mem *mem)
{
    char *pwd;

    pwd =  my_getenv(my_env, "PWD");
    close(mem->fd_exit_statue[0]);
    write(1, pwd, ft_strlen(pwd));
    write(1, "\n", 1);
    mem->exit_statue = 1;
    write(mem->fd_exit_statue[1], &mem->exit_statue, sizeof(mem->exit_statue));
    close(mem->fd_exit_statue[1]);
    free(pwd);
    return (1);
}
