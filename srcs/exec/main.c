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
	The arrow color is red if the previous command failed
*/
char	*get_prompt(t_mem *mem)
{
	char	*prompt;
	char	*pwd;
	char	*temp;
	char	*start;

	pwd = my_getenv(mem->my_env, "PWD");
	if (pwd)
	{
		temp = ft_strjoin("\n\033[36m", pwd);
		free(pwd);
		start = ft_strjoin(temp, "\033[0m\n");
		free(temp);
	}
	else
		start = ft_strdup("\n\033[36mminishell\033[0m ");
	if (mem->last_cmd_exit_statue == 0)
		prompt = ft_strjoin(start, "\033[32m❯\033[0m ");
	else
		prompt = ft_strjoin(start, "\033[31m❯\033[0m ");
	free(start);
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
			return (NULL);
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

/*
	Return the a copy of env
	Return NULL on malloc error
*/

char    **copy_env(char **env)
{
    char **my_env;
    int i;
    int len;

    len = 0;
    i = 0;
    while (env[i++])
        len++;
    my_env = (char **)malloc(sizeof(char *) * (len + 2));
	if (!my_env)
		return NULL;
    i = 0;
    while (env[i])
    {
        my_env[i] = ft_strdup(env[i]);
        i++;
    }
    my_env[i] = NULL;
    return my_env;
}

int	main(int ac, char **av, char **env)
{
	t_mem		*mem;
	t_cmdlst	*command_list;
	char		*str;

	mem = initialize_mem();
	signal(SIGINT, handler);
	mem->path_tab = ft_split(getenv("PATH"), ':');
	mem->my_env = copy_env(env);
	ft_printf("\033[1;1H\033[2J");
	while (42)
	{
		str = take_input(mem);
		if (!str)
			continue ;
		command_list = parsing(str);
		if (!command_list)
			continue ;
		execute3(command_list, env, mem);
		cmdlst_clear(&command_list);
		free(str);
	}
	return (0);
}
