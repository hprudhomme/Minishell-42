# include "../include/minishell.h"

t_mem	*initialize_mem(void)
{
	t_mem	*mem;

	mem = (t_mem *)malloc(sizeof(t_mem));
	mem->exec_loop = (t_exec_loop *)malloc(sizeof(t_exec_loop));
	mem->my_env = NULL;
    return (mem);
}