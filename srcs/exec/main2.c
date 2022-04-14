#include "../../include/minishell.h"

int ctrlC = 0;

/*
	Return the value of the given env name
	Return NULL if the value doesn't exist
	Return NULL on malloc error
*/
char	*my_getenv(char **env, char *elem)
{
	char	*str;
	int		index;
	int		elem_len;

	elem_len = ft_strlen(elem);
	index = 0;
	while (env[index])
	{
		if (ft_strncmp(elem, env[index], elem_len) == 0)
			break ;
		index++;
	}
	if (!env[index])
		return (NULL);
	str = ft_strdup(env[index] + elem_len + 1);
	if (!str)
		return (NULL);
	return (str);
}

/*
	Return a string containing the prompt
	That string is malloced, it need to be free
	Return NULL on malloc error
	If PWD exist, return :
		/home/cestoliv/Documents/DOCS/IT/Dev/42cursus/Minishell-42
		>
	If PWD doesn't exist, return :
		minishell >
*/
char	*get_prompt(t_mem *mem)
{
	char	*prompt;
	char	*pwd;
	char	*temp;

	pwd = my_getenv(mem->my_env, "PWD");
	if (pwd)
	{
		temp = ft_strjoin("\n\033[36m", pwd);
		free(pwd);
		if (!temp)
			return (NULL);
		prompt = ft_strjoin(temp, "\033[0m\n\033[32m❯\033[0m ");
		free(temp);
		if (!prompt)
			return (NULL);
	}
	else
	{
		prompt = ft_strdup("\n\033[36mminishell\033[0m \033[32m❯\033[0m ");
		if (!prompt)
			return (NULL);
	}
	return (prompt);
}

char	*take_input(t_mem *mem)
{
	char	*buf;
	char	*prompt;

	rl_getc_function = getc;
	prompt = get_prompt(mem);
	buf = readline(prompt);
	free(prompt);
	if (!buf)
	{
		if (ctrlC)
		{
			ctrlC = 0;
			return NULL;
		}
		else
		{
			free_mem(mem, 1);
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
        printf("outfiles_len = %d\n", outlst_len(lst->outfiles));
		lst = lst->next;
	}
}

int main(int ac, char **av, char **env)
{
    t_mem *mem;
    t_cmdlst *command_list;
    char *str;

    mem = initialize_mem();
    signal(SIGINT, handler);
    mem->path_tab = ft_split(getenv("PATH"), ':');
    mem->my_env = my_getenvs(env);
	ft_printf("\033[2J"); // Clear screen
    while (42)
    {
		str = take_input(mem);
        if (!str)
			continue;
        command_list = parsing(str);
        execute3(command_list, env, mem);
        cmdlst_clear(&command_list);
        free(str);
    }
    return 0;
}
