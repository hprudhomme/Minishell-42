#include "../../include/minishell.h"

/*
	return a path used as first parameter of execve fct
*/

char    *find_exec_path(char **path_tab, char *cmd, char *right_path)
{
    int i;
    int j;
    int x;

	if (cmd[0] == '.' || cmd[0] == '/')
		return (ft_strdup(cmd));
	if (!path_tab)
		return (NULL);
    i = 0;
    while (path_tab[i])
    {
        j = 0;
        x = 0;
        right_path = malloc(sizeof(char) * 150);
        while (path_tab[i][j])
            right_path[x++] = path_tab[i][j++];
        right_path[x] = '/';
        x++;
        j = 0;
        while (cmd[j])
            right_path[x++] = cmd[j++];
        right_path[x] = '\0';
        if (access(right_path, F_OK) == 0)
            return right_path;
        free(right_path);
        i++;
    }
    return NULL;
}

/*
	return redirect_file_path for outfiles
*/

char    *find_path_redirect_file(char *pwd, char *actuel, char *redirect_path)
{
    int i;
    int j;

    i = 0;
    j = 0;
    redirect_path = malloc(sizeof(char) * (ft_strlen(pwd) + ft_strlen(actuel) + 3));
    if (!redirect_path)
        return NULL;
    while (pwd[i])
        redirect_path[j++] = pwd[i++];
    redirect_path[j] = '/';
    j++;
    i = 0;
    while (actuel[i])
        redirect_path[j++] = actuel[i++];
    redirect_path[j] = '\0';
    return (redirect_path);
}
