/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 09:08:48 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/06 09:08:15 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Return the end of the first arg of given str
	It's gonna find the end index of the arg after the quotes
		(it takes the closing quote index as parameter)
	It return the index of the first space except if that space
	is after a &&, ||, |, <<, <, >> or >, it's gonna return the
	index just before that characters
*/
int	get_arg_end(char *str, int quote_index)
{
	char	**splitchar;
	int		end_index;
	int		test_index;
	int		cur;

	splitchar = ft_split("&& || | << < >> > &", ' ');
	if (!splitchar)
		return (0);
	end_index = index_of(str + quote_index, " ", 1);
	cur = -1;
	while (splitchar[++cur])
	{
		test_index = index_of(str + quote_index, splitchar[cur], 1);
		if (test_index < end_index)
		{
			strarr_free(splitchar);
			return (test_index + quote_index);
		}
	}
	strarr_free(splitchar);
	return (end_index + quote_index);
}

/*
	Return the end of the first arg of given str
	It's like a wrapper for get_arg_end() that jump directly to the closing quotes
	It return get_arg_end() with the index of the closing quote
		(if the arg starts with quotes, index_of need to find the first quote,
		if it doesn't start with quotes but contains quotes,
			index_of need to find the second quote, because the first is the opening quote
	Return -2 if there is not any quotes
*/
int	get_quotes_end(char *str, int e_end)
{
	int	end_index;

	end_index = -2;
	if (str[0] == '\'')
		end_index = get_arg_end(str, index_of(str + 1, "'", 1) + 2);
	else if (e_end > -1 && index_of(str, "'", 1) < e_end)
		end_index = get_arg_end(str, index_of(str + 1, "'", 2) + 2);
	else if (str[0] == '"')
		end_index = get_arg_end(str, index_of(str + 1, "\"", 1) + 2);
	else if (e_end > -1 && index_of(str, "\"", 1) < e_end)
		end_index = get_arg_end(str, index_of(str + 1, "\"", 2) + 2);
	return (end_index);
}

/*
	Return the end of the first arg of given str
	e_end is equal to the return of get_arg_end
		on the current string (with a quote_index = 0)
	A e_end = to -1 means that str start with a special char
		like quotes, &, |, < or >
	It can find if the arg is actually longer than the e_end
		because of some quotes (with get_quotes_end)
	or if it's lower because of a &&, ||, |, <<, <, >> or > before
*/
int	get_end_index(char *str, int e_end)
{
	int		end_index;
	char	**splitchar;
	int		cur;

	if (e_end == 0)
		return (0);
	splitchar = ft_split("&& || | << < >> > &", ' ');
	if (!splitchar)
		return (0);
	end_index = get_quotes_end(str, e_end);
	if (end_index == 0)
		return (strarr_free(splitchar));
	if (end_index != -2)
		return (end_index + strarr_free(splitchar));
	cur = -1;
	while (splitchar[++cur])
	{
		if ((e_end > -1 && index_of(str, splitchar[cur], 1) < e_end))
			return (index_of(str, splitchar[cur], 1) + strarr_free(splitchar));
		if (index_of(str, splitchar[cur], 1) == 0)
			return (ft_strlen(splitchar[cur]) + strarr_free(splitchar));
	}
	return (e_end + strarr_free(splitchar));
}

/*
	Split the given command in the given args list
	Works like a split on spaces, but it also split on <, <<, >, >>, &&, |, ||
	Of course, it doesn't split on these characters if they are surrounded
	by simple or double quotes

	E.g.: `echo 'Hello World' && cat -n 5 Makefile`
			return : ["echo", "'Hello World'", "&&", "cat", "-n", "5", "Makefile"]
*/
int	split_args(t_list **args, char *cmd)
{
	int		cur;
	char	*arg;
	int		end_index;

	cur = -1;
	while (cmd[++cur])
	{
		if (cmd[cur] == ' ')
			continue ;
		if (cmd[cur] == '\'' || cmd[cur] == '"' || cmd[cur] == '<'
			|| cmd[cur] == '&' || cmd[cur] == '|' || cmd[cur] == '>')
			end_index = get_end_index(cmd + cur, -1);
		else
			end_index = get_end_index(cmd + cur, get_arg_end(cmd + cur, 0));
		if (!end_index)
			return (lst_clear(args));
		arg = ft_strldup(cmd + cur, end_index);
		if (!arg)
			return (lst_clear(args));
		if (!lst_append(args, arg))
			return (lst_clear(args));
		cur += ft_strlen(arg) - 1;
	}
	return (1);
}

/*
	Main parsing function, return a list of commands
	Start by splitting the command in a list of args with split_args(),
	then parse that string list into a list of commands with create_command_lst()
	Return NULL on malloc error
	Return NULL on syntax error
*/
t_cmdlst	*parsing(char *command)
{
	t_cmdlst	*command_list;
	t_list		*args;

	args = NULL;
	if (check_quotes(command))
		return (NULL);
	if (!split_args(&args, command))
		return (NULL);
	if (check_specials(args))
	{
		lst_clear(&args);
		return (NULL);
	}
	if (!create_command_lst(&command_list, args))
	{
		lst_clear(&args);
		return (NULL);
	}
	lst_clear(&args);
	return (command_list);
}
