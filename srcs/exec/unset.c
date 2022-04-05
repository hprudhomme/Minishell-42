#include "../../include/minishell.h"

char    **ft_unset(char **my_env, char *s)
{
    char **new;
    char **temp;
    int i;
    int j;


    if (!is_in_env(my_env, s))
        return my_env;
    i = 0;
    j = 0;
    new = (char **)malloc(sizeof(char *) * (tab_2d_len(my_env)));
    if (!new)
        return NULL;
    i = 0;
    while (my_env[i])
    {
        temp = ft_split(my_env[i], '=');
        if (strcmp(temp[0], s) == 0)
            i++;
        else
            new[j++] = ft_strdup(my_env[i++]);
        free_tab_2d(temp);
    }
    new[j] = NULL;
    free_tab_2d(my_env);
    return new;
}
