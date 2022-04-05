#include "../../include/minishell.h"

int my_env_place_elem(char **my_env, char *elem/*"PATH"*/)
{
    int path_len;
    int index;

    path_len = ft_strlen(elem);
    index = 0;
    while (my_env[index])
    {
        if (ft_strncmp(elem, my_env[index], path_len) == 0)
            break ;
        index++;
    }
    return index;
}

char **change_pwd(char **temp2, char **my_env)
{
    int env_place;
    char *new_pwd;

    env_place = my_env_place_elem(my_env, "PWD");
    if (tab_2d_len(temp2) == 0)
        new_pwd = concat_path(temp2, "PWD=/");
    else
        new_pwd = concat_path(temp2, "PWD=");
    free(my_env[env_place]);
    my_env[env_place] = ft_strdup(new_pwd);
    free(new_pwd);
    return my_env;
}

char **change_oldpwd(char *pwd, char **my_env)
{
    char *new_old_pwd;
    int old_env_place;

    old_env_place = my_env_place_elem(my_env, "OLDPWD");
    new_old_pwd = ft_strjoin( "OLDPWD=", pwd);
    free(my_env[old_env_place]);
    my_env[old_env_place] = ft_strdup(new_old_pwd);
    free(new_old_pwd);
    return my_env;
}

char **change_my_env(char **cmd, char **my_env)
{
    char **temp;
    char **temp2;
    char *pwd;
    int i;

    i = 0;
    temp = ft_split(cmd[1], '/');
    pwd = my_getenv(my_env, "PWD");
    temp2 = ft_split(pwd, '/');
    while (temp[i])
    {
        if (strcmp(temp[i], "..") == 0)
            temp2 = supp_last_elem_tab2d(temp2);
        else
            temp2 = append_tab_2d(temp2, temp[i]);
        i++;
    }
    my_env = change_pwd(temp2, my_env);
    my_env = change_oldpwd(pwd, my_env);
    free_tab_2d(temp);
    free_tab_2d(temp2);
    return my_env;
}

void ft_cd(char **cmd, char **my_env)
{
    if (chdir(cmd[1]) == -1)
    {
        write(1, strerror( errno ), ft_strlen(strerror( errno )));
        write(1, "\n", 1);
    }
    else
        my_env = change_my_env(cmd, my_env);
}
