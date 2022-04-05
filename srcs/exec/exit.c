#include "../../include/minishell.h"

void ft_exit(t_list2 *list)
{
    free_list(list);
    if (list)
        free(list);
    exit(0);
}
