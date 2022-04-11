#include "../../include/minishell.h"

int    ft_echo(char **s, t_mem *mem)
{
    char *tmp;
    close(mem->fd_exit_statue[0]);
    int i;
    int x;

    // if (strcmp(s[1], "$?") == 0)
    // {
    //     write(1, "x = ", 4);
    //     write(1, ft_itoa(mem->last_cmd_exit_statue), ft_strlen(ft_itoa(mem->last_cmd_exit_statue)));
    //     write(1, "\n", 1);
    //     mem->exit_statue = 0;
    //     write(mem->fd_exit_statue[1], &mem->exit_statue, sizeof(mem->exit_statue));
    //     close(mem->fd_exit_statue[1]);
    //     return 1;
    // }
    // i = 0;
    // while (s[1][i])
    // {
    //     if (s[1][i] == ')')
    //     {
    //         mem->exit_statue = 1;
    //         write(mem->fd_exit_statue[1], &mem->exit_statue, sizeof(mem->exit_statue));
    //         return 1;
    //     }
    //     i++;
    // }
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
    mem->exit_statue = 0;
    write(mem->fd_exit_statue[1], &mem->exit_statue, sizeof(mem->exit_statue));
    close(mem->fd_exit_statue[1]);
    return 1;
}
