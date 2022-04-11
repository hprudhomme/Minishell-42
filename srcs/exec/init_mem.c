#include "../../include/minishell.h"

void 	init_exec_loop(t_exec_loop *exec_loop)
{
	exec_loop->redirect_path = NULL;
	exec_loop->right_path = NULL;
}

t_mem	*initialize_mem(void)
{
	t_mem	*mem;

	mem = (t_mem *)malloc(sizeof(t_mem));
	mem->exec_loop = (t_exec_loop *)malloc(sizeof(t_exec_loop));
		init_exec_loop(mem->exec_loop);
	mem->my_env = NULL;
	mem->path_tab = NULL;
	mem->tmpfile = "buzz";
    return (mem);
}

void 	free_exec_loop(t_exec_loop *exec_loop)
{
	if (exec_loop->redirect_path)
		free(exec_loop->redirect_path);
	if (exec_loop->right_path)
		free(exec_loop->right_path);
	free(exec_loop);
}

void	free_mem(t_mem *mem, int exiting)
{
	if (mem->my_env)
		free_tab_2d(mem->my_env);
	if (mem->path_tab)
		free_tab_2d(mem->path_tab);
	if (mem->exec_loop)
		free_exec_loop(mem->exec_loop);
	if (mem)
		free(mem);
	if (exiting)
		exit(EXIT_SUCCESS);
}