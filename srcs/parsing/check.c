/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 08:21:01 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/06 09:12:33 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		if (command[cur] == '\'')
		{
			if (in_quotes == 0)
				in_quotes = 1;
			else if (in_quotes == 1)
				in_quotes = 0;
		}
		if (command[cur] == '"')
		{
			if (in_quotes == 0)
				in_quotes = 2;
			else if (in_quotes == 2)
				in_quotes = 0;
		}
		cur++;
	}
	if (in_quotes != 0)
		ft_printf("\033[91m%s\033[0m\n",
			"minishell: parse error, quotes are never closed");
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
			{
				ft_printf("\033[91m%s '%s'\033[0m\n",
					"minishell: parse error, near", it_args->content);
				return (1);
			}
			is_special = 1;
		}
		else
			is_special = 0;
		if (!it_args->next)
		{
			if (is_sep(it_args->content))
			{
				ft_printf("\033[91m%s '%s'\033[0m\n",
					"minishell: the command cannot end with", it_args->content);
				return (1);
			}
		}
		it_args = it_args->next;
	}
	return (0);
}
