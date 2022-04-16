#include "../../include/minishell.h"

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
		if (!ft_strcmp(elem, env[index]))
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
   Return the a copy of env
   Return NULL on malloc error
   */

char	**copy_env(char **env)
{
	char	**my_env;
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (env[i++])
		len++;
	my_env = (char **)malloc(sizeof(char *) * (len + 2));
	if (!my_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		my_env[i] = ft_strdup(env[i]);
		i++;
	}
	my_env[i] = NULL;
	return (my_env);
}

/*
   return index of given elem in env
   */

int	my_env_index_elem(char **my_env, char *elem)
{
	int	path_len;
	int	index;

	path_len = ft_strlen(elem);
	index = 0;
	while (my_env[index])
	{
		if (ft_strncmp(elem, my_env[index], path_len) == 0)
			break ;
		index++;
	}
	return (index);
}

int	ft_env(t_mem *mem)
{
	int	x;

	x = -1;
	while (mem->my_env[++x])
		ft_printf("%s\n", mem->my_env[x]);
	mem->exit_statue = 0;
	return (1);
}
