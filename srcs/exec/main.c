/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 09:01:31 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/20 12:32:13 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_pid = 0;

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
		prompt = ft_strjoin(start, "\001\033[32m\002>\001\033[0m\002 ");
	else
		prompt = ft_strjoin(start, "\001\033[31m\002>\001\033[0m\002 ");
	free(start);
	return (prompt);
}

/*
	On SIGINT => new prompt
	On SIGQUIT => nothing
*/
void	handle_signals(int signo)
{
	if (g_pid)
		return ;
	if (signo == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_printf("  \b\b");
	}
}

char	*take_input(t_mem *mem)
{
	char	*buf;
	char	*prompt;

	prompt = get_prompt(mem);
	buf = readline(prompt);
	free(prompt);
	if (!buf)
	{
		ft_printf("\n");
		exit(free_mem(mem));
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

	(void)ac;
	(void)av;
	g_pid = 0;
	mem = initialize_mem();
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
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
	return (free_mem(mem));
}
