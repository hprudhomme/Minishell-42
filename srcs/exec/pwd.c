#include "../../include/minishell.h"

int  ft_pwd(char **my_env, t_mem *mem)
{
    close(mem->fd_exit_statue[0]);
    write(1, my_getenv(my_env, "PWD"), ft_strlen(getenv("PWD")));
    write(1, "\n", 1);
    mem->exit_statue = 1;
    write(mem->fd_exit_statue[1], &mem->exit_statue, sizeof(mem->exit_statue));
    close(mem->fd_exit_statue[1]);
    return (1);
}
