#include "../../include/minishell.h"

void ft_exit(t_mem *mem, t_cmdlst *lst)
{
    free_mem(mem, 1);
    cmdlst_clear(&lst);
    exit(0);
}
