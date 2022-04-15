/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 08:21:01 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/15 11:25:49 by ocartier         ###   ########.fr       */
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
		ft_printf("\033[91m%s\033[0m\n",
			"minishell: parse error, quotes are never closed");
	}
	else if (error_code == 2)
	{
		ft_printf("\033[91m%s '%s'\033[0m\n",
			"minishell: parse error, near", content);
	}
	else if (error_code == 3)
	{
		ft_printf("\033[91m%s '%s'\033[0m\n",
			"minishell: the command cannot end with",
			content);
	}
	return (1);
}

/*
	Return 1 on syntax error, 0 if there is no error
	Error : An openned quote in not closed
*/
int	check_quotes(char *command)
{
	int	cur;
	int	in_quotes;

	cur = 0;
	in_quotes = 0;
	while (command[cur])
	{
		set_in_quotes(command[cur], &in_quotes);
		cur++;
	}
	if (in_quotes != 0)
		print_error(1, NULL);
	return (in_quotes != 0);
}

/*
	Return 1 on syntax error, 0 if there is no error
	Error :	A special is followed by a special
			The command ends with a special

	E.g.:	echo 42 > && cat Makefile
			echo 42 &&
*/
int	check_specials(t_list *args)
{
	t_list	*it_args;
	int		is_special;

	it_args = args;
	is_special = 0;
	while (it_args)
	{
		if (is_sep(it_args->content))
		{
			if (is_special)
				return (print_error(2, it_args->content));
			is_special = 1;
		}
		else
			is_special = 0;
		if (!it_args->next)
		{
			if (is_sep(it_args->content) && ft_strcmp(it_args->content, ";"))
				return (print_error(3, it_args->content));
		}
		it_args = it_args->next;
	}
	return (0);
}
