/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 09:01:31 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/18 12:14:52 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_crtl_c = 0;

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
		temp = ft_strjoin("\n\001\033[36m\002", pwd);
		free(pwd);
		start = ft_strjoin(temp, "\001\033[0m\002\n");
		free(temp);
	}
	else
		start = ft_strdup("\n\001\033[36m\002minishell\001\033[0m\002 ");
	if (mem->last_cmd_exit_statue == 0)
		prompt = ft_strjoin(start, "\001\033[32m\002❯\001\033[0m\002 ");
	else
		prompt = ft_strjoin(start, "\001\033[31m\002❯\001\033[0m\002 ");
	free(start);
	return (prompt);
}

void	handler(int i)
{
	(void)i;
	g_crtl_c = 1;
}

int	not_buf(t_mem *mem)
{
	if (g_crtl_c)
	{
		g_crtl_c = 0;
		return (0);
	}
	else
	{
		free_mem(mem, 1);
		return (1);
	}
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
		if (not_buf(mem))
			exit(0);
		else
			return (NULL);
	}
	if (ft_strlen(buf) == 0)
	{
		free(buf);
		return (NULL);
	}
	add_history(buf);
	return (buf);
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
		free(str);
		if (!command_list)
			continue ;
		execute(command_list, mem);
		cmdlst_clear(&command_list);
	}
	return (0);
}
