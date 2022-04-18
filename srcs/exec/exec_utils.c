/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 09:00:56 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/18 21:09:47 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_up_outfiles(t_mem *mem, t_cmdlst *lst)
{
	if (lst->outfiles->action == 0)
	{
		mem->exec_loop->redirect_file_path
			= find_path_redirect_file(getenv("PWD"),
				lst->outfiles->filename, mem->exec_loop->redirect_file_path);
			mem->exec_loop->fdout = open(mem->exec_loop->redirect_file_path,
				O_CREAT | O_WRONLY | O_TRUNC, S_IRWXO | S_IRWXU | S_IRWXG);
	}
	else if (lst->outfiles->action == 1)
	{
		mem->exec_loop->redirect_file_path
			= find_path_redirect_file(getenv("PWD"),
				lst->outfiles->filename, mem->exec_loop->redirect_file_path);
			mem->exec_loop->fdout = open(mem->exec_loop->redirect_file_path,
				O_APPEND | O_CREAT | O_WRONLY, S_IRWXO | S_IRWXU | S_IRWXG);
	}
}

/*
	if next is not a pipe
		-> if outfiles (> or >>)
		-> else
	else
		-> create a pipe
		it's all about where u need to put the output :)
*/

void	set_up_output(t_mem *mem, t_cmdlst *lst, int i)
{
	if (i > 0)
		lst->outfiles = lst->outfiles->next;
	if (lst->todo_next != 1)
	{
		if (lst->outfiles)
			set_up_outfiles(mem, lst);
		else
			mem->exec_loop->fdout = dup(mem->exec_loop->tmpout);
	}
	else
	{
		pipe(mem->exec_loop->fdpipe);
		mem->exec_loop->fdout = mem->exec_loop->fdpipe[1];
		mem->exec_loop->fdin = mem->exec_loop->fdpipe[0];
	}
}

/*
   init the loop of outfiles
   */

void	init_outlst_loop(t_mem *mem, t_cmdlst *lst, int i)
{
	dup2(mem->exec_loop->fdin, 0);
	close(mem->exec_loop->fdin);
	set_up_output(mem, lst, i);
	dup2(mem->exec_loop->fdout, 1);
	close(mem->exec_loop->fdout);
}

/*
   save last exit statue for && || $? behaviors
   return 1 if :
   -> exit statut = 0 and to_do_next is ||
   -> exit statut != 0 and to_do_next is &&
   if to_do_next is || or && reset and init, cuz it's like doing a new cmd
   */

int	save_last_exit_statue(t_mem *mem, t_cmdlst *lst)
{
	mem->last_cmd_exit_statue = mem->exit_statue;
	if (mem->exit_statue == 0 && lst->todo_next == 3)
		return (1);
	if (mem->exit_statue != 0 && lst->todo_next == 2)
		return (1);
	if (lst->todo_next == 2 || lst->todo_next == 3)
	{
		reset_exec(mem);
		init_exec(mem, lst);
	}
	return (0);
}

/*
   if builtin cmd do things for
   if not builtin call execve
   */

void	init_exec_cmd(t_mem *mem, t_cmdlst *lst)
{
	mem->exec_path = NULL;
	mem->path_env = my_getenv(mem->my_env, "PATH");
	if (mem->path_tab)
		free_tab_2d(mem->path_tab);
	mem->path_tab = ft_split(mem->path_env, ':');
	mem->exec_path = find_exec_path(mem->path_tab, lst->command,
			mem->exec_path);
}
