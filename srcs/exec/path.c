#include "../../include/minishell.h"

char    *find_right_path(char **path_tab, char *cmd, char *right_path)
{
    int i;
    int j;
    int x;
    char    *tmp;

    i = 0;
    while (path_tab[i])
    {
        j = 0;
        x = 0;
        // printf("l = %ld\n", ft_strlen(path_tab[i] + ft_strlen(cmd) + 2));
        right_path = malloc(sizeof(char) * 150);
        // if (!right_path)
        // {
        //     i++;
        //     continue ;
        // }
        while (path_tab[i][j])
        {
            right_path[x] = path_tab[i][j];
            j++;
            x++;
        }
        right_path[x] = '/';
        x++;
        j = 0;
        while (cmd[j])
        {
            right_path[x] = cmd[j];
            x++;
            j++;
        }
        right_path[x] = '\0';
        if (access(right_path, F_OK) == 0)
            return right_path;

        // printf("second path = %s\n", right_path);
        // printf("access = %d\n", access(right_path, F_OK));
        free(right_path);
        i++;
    }
    return NULL;
}

char    *find_path_redirect_file(char *pwd, char *actuel, char *redirect_path)
{
    int i;
    int j;

    i = 0;
    j = 0;
    redirect_path = malloc(sizeof(char) * (ft_strlen(pwd) + ft_strlen(actuel) + 3));
    while (pwd[i])
    {
        redirect_path[j] = pwd[i];
        i++;
        j++;
    }
    redirect_path[j] = '/';
    j++;
    i = 0;
    while (actuel[i])
    {
        redirect_path[j] = actuel[i];
        i++;
        j++;
    }
    redirect_path[j] = '\0';
    return (redirect_path);
}
