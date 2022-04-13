/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:50:09 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/13 10:50:45 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Print the error corresponding to the given error code
*/
static int	print_error(int error_code, char *content)
{
	if (error_code == 1)
	{
		ft_printf("\033[91m%s '%c'\033[0m\n",
			"export: name cannot start with", *content);
	}
	else if (error_code == 2)
	{
		ft_printf("\033[91m%s '%c'\033[0m\n",
			"export: not valid in this context:", *content);
	}
	return (1);
}

/*
	Return 1 on syntax error, 0 if there is no error
	Error :	The env name starts with a number
			The env name contains other chars than [A-Z][a-z][0-9]_
			The arg doesn't contain an equal sign
	Display an error with ft_printf when the error is not the missing equal sign

	E.g.:	1name=oliv
			na-me=oliv
			name = oliv
*/
int	check_format(char	*arg)
{
	int	cur;
	int	has_equal;

	if (!ft_isalpha(arg[0]))
		return (print_error(1, &arg[0]));
	cur = 0;
	has_equal = 0;
	while (arg[cur])
	{
		if (arg[cur] == '=')
			has_equal = 1;
		else if (!ft_isalnum(arg[cur]) && arg[cur] != '_')
			if (!has_equal)
				return (print_error(2, &arg[cur]));
		cur++;
	}
	if (!has_equal)
		return (1);
	return (0);
}

char    **ft_export(t_mem *mem, char *s)
{
    char **new;
    char **temp;
    int i;

    i = 0;
    if (check_format(s))
        return mem->my_env;
    temp = ft_split(s, '=');
    if (is_in_env(mem->my_env, temp[0]))
        mem->my_env = ft_unset(mem, temp[0]);
    free_tab_2d(temp);
    new = (char **)malloc(sizeof(char *) * (tab_2d_len(mem->my_env) + 2));
    if (!new)
        return NULL;
    while (mem->my_env[i])
    {
        new[i] = ft_strdup(mem->my_env[i]);
        i++;
    }
    new[i] = ft_strdup(s);
    i++;
    new[i] = NULL;
    free_tab_2d(mem->my_env);
    return new;
}

char    **ft_exports(t_mem *mem, char **args)
{
    int i;

    close(mem->fd_exit_statue[0]);
    i = 0;
    while (args[i])
    {
        if (strcmp(args[i], "export") == 0)
            break ;
        i++;
    }
    i++;
    while (args[i])
    {
        mem->my_env = ft_export(mem, args[i]);
        i++;
    }
    mem->exit_statue = 0;
    write(mem->fd_exit_statue[1], &mem->exit_statue, sizeof(mem->exit_statue));
    close(mem->fd_exit_statue[1]);
    return (mem->my_env);
}
