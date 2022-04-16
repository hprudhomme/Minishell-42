#include "../../include/minishell.h"

/*
   Return 2 if is builtin and change env
   Return 1 if is builtin
   return 0 if not builtin
   */

int	is_builtin(char *cmd)
{
	if (strcmp(cmd, "cd") == 0)
		return (2);
	if (strcmp(cmd, "exit") == 0)
		return (2);
	if (strcmp(cmd, "pwd") == 0)
		return (1);
	if (strcmp(cmd, "env") == 0)
		return (1);
	if (strcmp(cmd, "echo") == 0)
		return (1);
	if (strcmp(cmd, "export") == 0)
		return (2);
	if (strcmp(cmd, "unset") == 0)
		return (2);
	return (0);
}

/*
   init var for exec loop
   call before exec loop or at the end of loop when next_to_do is && or ||
   */

void	init_exec(t_mem *mem, t_cmdlst *lst)
{
	mem->exec_loop->tmpin = dup(0);
	mem->exec_loop->tmpout = dup(1);
	if (lst->infiles)
		mem->exec_loop->fdin = open(lst->infiles[0], O_RDONLY);
	else
		mem->exec_loop->fdin = dup(mem->exec_loop->tmpin);
	mem->exit_statue = 0;
}

/*
   reset var for exec loop
   call after exec loop or at the end of loop when next_to_do is && or ||
   */

void	reset_exec(t_mem *mem)
{
	dup2(mem->exec_loop->tmpin, 0);
	dup2(mem->exec_loop->tmpout, 1);
	close(mem->exec_loop->tmpin);
	close(mem->exec_loop->tmpout);
	if (mem->exec_loop->redirect_file_path)
		free(mem->exec_loop->redirect_file_path);
	mem->exec_loop->redirect_file_path = NULL;
	mem->exec_loop->right_path = NULL;
	mem->exit_statue = 0;
}

int	is_exiting(t_cmdlst *lst)
{
	if ((strcmp(lst->command, "exit") == 0) && ((lst->todo_next == 0
				&& cmdlist_len(lst) == 1) || lst->todo_next == 2
			|| lst->todo_next == 3))
		return (1);
	return (0);
}

int	exec_builtin(t_mem *mem, t_cmdlst *lst)
{
	if (strcmp(lst->command, "cd") == 0 || strcmp(lst->command, "exit") == 0
		|| strcmp(lst->command, "export") == 0
		|| strcmp(lst->command, "unset") == 0)
		return (0);
	if (strcmp(lst->command, "pwd") == 0)
		ft_pwd(mem);
	if (strcmp(lst->command, "env") == 0)
		ft_env(mem);
	if (strcmp(lst->command, "echo") == 0)
		ft_echo(lst->args, mem);
	return (1);
}
