#include "../../include/minishell.h"

int	ft_env(t_mem *mem)
{
	int	x;

	x = -1;
	while (mem->my_env[++x])
		ft_printf("%s\n", mem->my_env[x]);
	mem->exit_statue = 0;
	return (1);
}
