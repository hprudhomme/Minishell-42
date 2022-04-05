#include "../../include/minishell.h"

void    ft_echo(char **s)
{
    int i;
    int x;

    x = 1;
    if (s[1] && strcmp(s[1], "-n") == 0)
        x = 2;
    i = x;
    while (s[i])
    {
        if (i > x)
            write(1, " ", 1);
        write(1, s[i], ft_strlen(s[i]));
        i++;
    }
    if (x == 1 || tab_2d_len(s) == 1)
        write(1, "\n", 1);
}
