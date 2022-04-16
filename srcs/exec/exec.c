#include "../../include/minishell.h"

/*
   Print the error corresponding to the given error code
   */
static int	print_error(int error_code, char *content)
{
	if (error_code == 14)
	{
		ft_printf("\033[91m%s '%s'\033[0m\n",
			"minishell: command not found:", content);
	}
	else if (error_code == 13)
	{
		ft_printf("\033[91m%s '%s'\033[0m\n",
			"minishell: permission denied:", content);
	}
	return (1);
}

void	exec_cmd(t_mem *mem, t_cmdlst *lst)
{
	init_exec_cmd(mem, lst);
	if (is_builtin(lst->command))
	{
		if (!exec_builtin(mem, lst))
			exit(0);
	}
	else
	{
		if (execve(mem->exec_path, lst->args, mem->my_env) == -1)
		{
			if (errno == 14 || errno == 13)
				print_error(errno, lst->command);
			else
				ft_printf("%d %s\n", errno, strerror(errno));
			free_path(mem);
			exit(1);
		}
	}
	free_path(mem);
	exit(0);
}

/*
   exec builtin cmd that change env
   */

int	do_builtin(t_cmdlst *lst, t_mem *mem)
{
	if (strcmp(lst->command, "cd") == 0 && lst->todo_next != 1)
		ft_cd(lst->args, mem);
	if (strcmp(lst->command, "export") == 0 && lst->todo_next != 1)
		if (!ft_exports(mem, lst->args))
			return (0);
	if (strcmp(lst->command, "unset") == 0 && lst->todo_next != 1)
		if (!ft_unsets(mem, lst->args))
			return (0);
	return (1);
}

/*
   hearts of exec that loop over the number of outfiles
   create a child process with fork
   exec cmd
   */

void	exec_next(t_cmdlst *lst, t_mem *mem, int i)
{
	init_outlst_loop(mem, lst, i);
	mem->exec_loop->ret = fork();
	if (mem->exec_loop->ret == 0)
		exec_cmd(mem, lst);
	waitpid(mem->exec_loop->ret, &(mem->exit_statue), 0);
	if ((strcmp(lst->command, "cd") == 0 && lst->todo_next != 1)
		|| (strcmp(lst->command, "export") == 0 && lst->todo_next != 1)
		|| (strcmp(lst->command, "unset") == 0 && lst->todo_next != 1))
		do_builtin(lst, mem);
	if (lst->heredocs)
		delete_tpmfile(mem);
}

/*
   loop to execute one or multiple command in lst
   */

void	execute(t_cmdlst *lst, t_mem *mem)
{
	int	i;

	mem->exec_loop->redirect_file_path = NULL;
	init_exec(mem, lst);
	while (lst)
	{
		setup_infiles(lst, mem);
		if (is_exiting(lst))
			ft_exit(mem, lst);
		replace_quotes(&(lst->args), mem->my_env, mem->last_cmd_exit_statue);
		if (outlst_len(lst->outfiles) > 0)
			i = 0;
		else
			i = -1;
		while (i < outlst_len(lst->outfiles))
		{
			exec_next(lst, mem, i);
			i++;
		}
		if (save_last_exit_statue(mem, lst))
			lst = lst->next;
		lst = lst->next;
	}
	reset_exec(mem);
}
