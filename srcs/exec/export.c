/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:50:09 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/20 11:39:08 by ocartier         ###   ########.fr       */
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

/*
	Parse the current string (an arg) and add it to mem->my_env
	Return 0 on malloc error
	Return 1 on succeed
	Return 2 on command error (bad syntax, etc.)
*/
int	ft_export(t_mem *mem, char *s)
{
	char	**new;
	char	**temp;

	if (check_format(s))
		return (2);
	temp = ft_split(s, '=');
	if (!temp)
		return (0);
	if (is_in_env(mem->my_env, temp[0]))
	{
		new = ft_unset(mem, temp[0]);
		if (!temp)
			return (strarr_free(temp));
		strarr_free(mem->my_env);
		mem->my_env = new;
	}
	strarr_free(temp);
	if (!strarr_append(&(mem->my_env), s))
		return (0);
	return (1);
}

/*
   Run the function ft_export on every args
   Return 0 on malloc error (some env var may have been set)
   */
int	ft_exports(t_mem *mem, char **args)
{
	int	i;
	int	command_return;

	i = 1;
	mem->exit_statue = 0;
	while (args[i])
	{
		command_return = ft_export(mem, args[i]);
		if (command_return == 0)
			return (0);
		else if (command_return == 2)
			mem->exit_statue = 1;
		i++;
	}
	return (1);
}
