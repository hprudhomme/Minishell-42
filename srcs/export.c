# include "../include/minishell.h"

int     is_egal(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] == '=')
            return 1;
        i++;
    }
    return 0;
}

char    **ft_export(char **my_env, char *s)
{
    char **new;
    char **temp;
    int i;

    i = 0;
    if (!is_egal(s))
        return my_env;
    temp = ft_split(s, '=');
    if (is_in_env(my_env, temp[0]))
        my_env = ft_unset(my_env, temp[0]);
    free_tab_2d(temp);
    new = (char **)malloc(sizeof(char *) * (tab_2d_len(my_env) + 2));
    if (!new)
        return NULL;
    while (my_env[i])
    {
        new[i] = ft_strdup(my_env[i]);
        i++;
    }
    new[i] = ft_strdup(s);
    i++;
    new[i] = NULL;
    free_tab_2d(my_env);
    return new;
}