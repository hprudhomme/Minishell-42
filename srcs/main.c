#include "../include/minishell.h"

int ctrlC = 0;

char *my_getenv(char **env, char *elem/*"PATH"*/)
{
    char    *str;
    int     i;
    int     x;
    int path_len;
  /* je parcours l’env, je trouve la ligne qui commence par PATH*/
  /* j’envoie l’adresse de ce qui se trouve apres le ’=’ */

    path_len = ft_strlen(elem);
    int index = 0;
    while (env[index])
    {
        // if (env[index][0] == 'P' && env[index][1] == 'A' && env[index][2] == 'T' && env[index][3] == 'H')
        //     break ;
        if (ft_strncmp(elem, env[index], path_len) == 0)
            break ;
        index++;
    }
    str = malloc(sizeof(char) * (ft_strlen(env[index]) - path_len));

    i = path_len + 1;
    x = 0;
    while (env[index][i])
    {
        str[x] = env[index][i];
        i++;
        x++;
    }
    str[x] = '\0';
    return (str);
}

char	*take_input(void)
{
	char	*buf;

    // Changing readlin's getc function works due to getc returning -1 on a Ctrl+C, which causes readline to return NULL.
    rl_getc_function = getc;
	buf = readline("mon_prompt>>> ");
	if (!buf)
    {
        if (ctrlC)
        {
            ctrlC = 0;
            return NULL;
        }
        else
        {
            write(1, "\n", 1);
            exit(0);
        }
    }
	if (ft_strlen(buf) == 0)
	{
		free(buf);
		return (NULL);
	}
	add_history(buf);
	return (buf);
}

void    handler()
{
    ctrlC = 1;
    write(1, "\n", 1);
}

char    **my_getenvs(char **env)
{
    char **my_env;
    int i;
    int len;

    len = 0;
    i = 0;
    while (env[i++])
        len++;
    my_env = (char **)malloc(sizeof(char *) * (len + 2));
    i = 0;
    while (env[i])
    {
        my_env[i] = ft_strdup(env[i]);
        i++;
    }
    my_env[i] = NULL;
    return my_env;
}

int main(int ac, char **av, char **env)
{
    t_mem *mem;
    char *str;
    char *env_path;
    char ** array = NULL;
    int pid;
    int len;
    
    char **my_env;

    char **tab_esp_list;
    char **tab_pipe_split;
    char **path_tab;
    char *right_path;

    t_list2 *list;

    mem = initialize_mem();
    signal(SIGINT, handler);
    env_path = getenv("PATH");
    // printf("s = %s\n", env_path);
    path_tab = ft_split(env_path, ':');
    // int z = 0;
    // while (path_tab[z])
    // {
    //     printf("str = %s\n", path_tab[z]);
    //     z++;
    // }
    
    mem->my_env = my_getenvs(env);
    
    // if (chdir("buzz") == -1)
    // {
    //     printf("buzz\n");
    //     printf("%s\n", strerror( errno ));
    // }
    while (42)
    {
		str = take_input();
        if (!str)
			continue;

        // test &&
        tab_esp_list = ft_split(str, '&');
        free(str);
        int i = 0;
        while (i < tab_2d_len(tab_esp_list))
        {
            list = initialisation();
            tab_pipe_split = ft_split(tab_esp_list[i], '|');
            len = tab_2d_len(tab_pipe_split);
            do_list_simple_cmd(tab_pipe_split, list);
            check_redirection(list);
            execute2(list, path_tab, env, mem);

            free_list(list);
            if (list)
                free(list);
            free_tab_2d(tab_pipe_split);
            i++;
        }
    }
    free_tab_2d(my_env);
    return 0;
}
