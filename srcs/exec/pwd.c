#include "../../include/minishell.h"

/*
   Minishell built-in function (pwd)
   Print the PWD from the env if found
   */
int	ft_pwd(t_mem *mem)
{
	char	*pwd;

	pwd = my_getenv(mem->my_env, "PWD");
	if (pwd)
	{
		write(1, pwd, ft_strlen(pwd));
		write(1, "\n", 1);
		mem->exit_statue = 0;
		free(pwd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		mem->exit_statue = 1;
		exit(EXIT_FAILURE);
	}
}
