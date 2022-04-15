#include "../../include/minishell.h"

/*
	if var isnt find return env without refreshing it
    else return a refresh env without this var
*/

char	**ft_unset(t_mem *mem, char *var)
{
	char	**new;
	char	**temp;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new = (char **)ft_calloc(strarr_len(mem->my_env) - 1, sizeof(char *));
	if (!new)
		return (NULL);
	while (mem->my_env[++i])
	{
		temp = ft_split(mem->my_env[i], '=');
		if (!temp)
			return (nil(free_array_n(new, j)));
		if (ft_strcmp(temp[0], var))
		{
			new[j++] = ft_strdup(mem->my_env[i]);
			if (!new[j - 1])
				return (nil(free_array_n(new, j - 1) + strarr_free(temp)));
		}
		strarr_free(temp);
	}
	return (new);
}

int	ft_unsets(t_mem *mem, char **args)
{
	int		i;
	char	**temp;

	mem->exit_statue = 0;
	i = 0;
	while (args[++i])
	{
		temp = ft_unset(mem, args[i]);
		if (!temp)
			return (0);
		strarr_free(mem->my_env);
		mem->my_env = temp;
	}
	return (1);
}
