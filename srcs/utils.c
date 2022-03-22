# include "../include/minishell.h"

int     tab_2d_len(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
        i++;
    return (i);
}
