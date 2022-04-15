#include "../../include/minishell.h"

/*
	return index of given elem in env
*/

int my_env_index_elem(char **my_env, char *elem/*"PATH"*/)
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

/*
	change path of pwd in env
    return env with new pwd
*/

char **change_pwd(char **temp2, char **my_env)
{
    int pwd_place;
    char *new_pwd;
    char **temp;
    int i;

    i = 0;
    pwd_place = my_env_index_elem(my_env, "PWD");
    temp = (char **)malloc(sizeof(char *) * (tab_2d_len(my_env) + 1));
    if (!temp)
        return NULL;
    pwd_place = my_env_index_elem(my_env, "PWD");
    new_pwd = concat_path(temp2, "PWD=");
    while (my_env[i])
    {
        if (i == pwd_place)            
            temp[i] = ft_strdup(new_pwd);
        else
            temp[i] = ft_strdup(my_env[i]);
        i++;
    }
    temp[i] = NULL;
    free_tab_2d(my_env);
    free(new_pwd);
    return temp;
}

/*
	change path of oldpwd in env
    return env with new oldpwd
*/

char **change_oldpwd(char *pwd, char **my_env)
{
    char *new_old_pwd;
    int old_env_index;

    old_env_index = my_env_index_elem(my_env, "OLDPWD");
    new_old_pwd = ft_strjoin( "OLDPWD=", pwd);
    free(my_env[old_env_index]);
    my_env[old_env_index] = ft_strdup(new_old_pwd);
    free(new_old_pwd);
    return my_env;
}

/*
	change path of pwd in env for absolute path
*/

char **change_pwd_absolute(char *path, char **my_env)
{
    int i;
    int pwd_index;
    char **temp;
    char *new_pwd;

    i = 0;
    temp = (char **)malloc(sizeof(char *) * (tab_2d_len(my_env) + 1));
    if (!temp)
        return NULL;
    pwd_index = my_env_index_elem(my_env, "PWD");
    new_pwd = ft_strjoin("PWD=", path);
    while (my_env[i])
    {
        if (i == pwd_index)            
            temp[i] = ft_strdup(new_pwd);
        else
            temp[i] = ft_strdup(my_env[i]);
        i++;
    }
    temp[i] = NULL;
    free_tab_2d(my_env);
    free(new_pwd);
    return temp;
}

/*
	change path of pwd in env for relativ path
*/

char **change_pwd_relativ(char *path, char **my_env)
{
    char **temp;
    char **temp2;
    char *pwd;
    int i;

    i = 0;
    pwd = my_getenv(my_env, "PWD");
    temp = ft_split(path, '/');
    temp2 = ft_split(pwd, '/');
    while (temp[i])
    {
        if (strcmp(temp[i], "..") == 0)
            temp2 = supp_last_elem_tab2d(temp2);
        else if (strcmp(temp[i], ".") != 0)
            temp2 = append_tab_2d(temp2, temp[i]);
        i++;
    }
    my_env = change_pwd(temp2, my_env);
    my_env = change_oldpwd(pwd, my_env);
    free_tab_2d(temp);
    free_tab_2d(temp2);
    free(pwd);
    return my_env;
}

char    **change_pwd_home(char **my_env)
{
    char *new_pwd;
    int pwd_index;
    char *home;

    home = my_getenv(my_env, "HOME");
    pwd_index = my_env_index_elem(my_env, "PWD");
    new_pwd = ft_strjoin( "PWD=", home);
    free(my_env[pwd_index]);
    my_env[pwd_index] = ft_strdup(new_pwd);
    free(new_pwd);
    free(home);
    return my_env;
}

/*
	change env (oldpwd and pwd) depending on if it's absolute or relativ path
*/

char **change_my_env(char **cmd, char **my_env)
{
    char *pwd;

    pwd = my_getenv(my_env, "PWD");
    if (!cmd[1])
    {
        my_env = change_pwd_home(my_env);
        my_env = change_oldpwd(pwd, my_env);
    }
    else if (cmd[1][0] == '/')
    {
        my_env = change_pwd_absolute(cmd[1], my_env);
        my_env = change_oldpwd(pwd, my_env);
    }
    else
        my_env = change_pwd_relativ(cmd[1], my_env);
    if (pwd)
        free(pwd);
    return my_env;
}

/*
	if can't change directory (chdir return -1), exit statut = 1
    else change env (pwd, oldpwd), exit statut = 0
*/

void ft_cd(char **cmd, t_mem *mem)
{
    int x;
    char *home;

    x = 1;
    home = my_getenv(mem->my_env, "HOME");
    if (!cmd[1])
    {
        if (chdir(home) == -1)
        {
            write(1, strerror( errno ), ft_strlen(strerror( errno )));
            write(1, "\n", 1);
            x = 0;
            mem->exit_statue = 1;
        }
    }
    else if (chdir(cmd[1]) == -1)
    {
        write(1, strerror( errno ), ft_strlen(strerror( errno )));
        write(1, "\n", 1);
        x = 0;
        mem->exit_statue = 1;
    }
    if (x)
    {
        mem->my_env = change_my_env(cmd, mem->my_env);
        mem->exit_statue = 0;
    }
    free(home);
}
