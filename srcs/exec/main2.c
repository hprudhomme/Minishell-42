#include "../../include/minishell.h"

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

void    print_outlst(t_outlst *lst)
{
    printf("buzz\n");
    while (lst)
    {
        if (lst->filename)
        {
            printf("filename : %s\n", lst->filename);
            printf("action : %d\n", lst->action);
        }
        
        lst = lst->next;
    }
}

void	printf_cmdlist(t_cmdlst *lst)
{
	int	cur;
	int	a_cur;

	cur = 0;
	while (lst)
	{
		cur++;
		printf("  -> %s\n     args: [", lst->command);
		a_cur = 0;
		while (lst->args && lst->args[a_cur])
		{
			printf("\"%s\",", lst->args[a_cur]);
			a_cur++;
		}
		printf("]\n");
		if (lst->todo_next == NEXT_OR)
			printf("     -> Next : OR\n");
		else if (lst->todo_next == NEXT_AND)
			printf("     -> Next : AND\n");
		else if (lst->todo_next == NEXT_PIPE)
			printf("     -> Next : PIPE\n");
		else
			printf("     -> Next : END\n");
		// printf("     outfiles (write): [");
		a_cur = 0;
        print_outlst(lst->outfiles);
		// while (lst->write_in && lst->write_in[a_cur])
		// {
		// 	printf("\"%s\",", lst->write_in[a_cur]);
		// 	a_cur++;
		// }
		// printf("]\n");
		// printf("     outfiles (append): [");
		// a_cur = 0;
		// while (lst->append_in && lst->append_in[a_cur])
		// {
		// 	printf("\"%s\",", lst->append_in[a_cur]);
		// 	a_cur++;
		// }
		printf("]\n");
		printf("     infiles: [");
		a_cur = 0;
		while (lst->infiles && lst->infiles[a_cur])
		{
			printf("\"%s\",", lst->infiles[a_cur]);
			a_cur++;
		}
		printf("]\n");
		printf("     heredocs: [");
		a_cur = 0;
		while (lst->heredocs && lst->heredocs[a_cur])
		{
			printf("\"%s\",", lst->heredocs[a_cur]);
			a_cur++;
		}
		printf("]\n");
		lst = lst->next;
	}
}

int main(int ac, char **av, char **env)
{
    t_mem *mem;
    char *str;
    char *env_path;
    char **tab_esp_list;
    t_cmdlst *command_list;

    char **my_env;
    char **path_tab;
    char *right_path;

    mem = initialize_mem();
    signal(SIGINT, handler);
    env_path = getenv("PATH");
    path_tab = ft_split(env_path, ':');

    mem->my_env = my_getenvs(env);
    while (42)
    {
		str = take_input();
        if (!str)
			continue;

        command_list = parsing(str);
        printf_cmdlist(command_list);
        free(str);
        // int i = 0;
        // while (i < tab_2d_len(tab_esp_list))
        // {
        //     command_list = parsing(str);
        //     print_cmdlist(command_list);
        //     execute3(command_list, path_tab, env, mem);
        //     i++;
        // }
    }
    free_tab_2d(my_env);
    return 0;
}