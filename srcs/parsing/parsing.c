/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 09:08:48 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/05 14:55:42 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_arg_end(char *str, int quote_index)
{
	char	**splitchar;
	int		end_index;
	int		test_index;
	int		cur;

	splitchar = ft_split("&& || | << < >> >", ' ');
	if (!splitchar)
		return (0);
	end_index = index_of(str + quote_index, " ", 1);
	cur = -1;
	while (splitchar[++cur])
	{
		test_index = index_of(str + quote_index, splitchar[cur], 1);
		if (test_index < end_index)
			return (test_index + quote_index + strarr_free(splitchar));
	}
	return (end_index + quote_index + strarr_free(splitchar));
}

int	get_quotes_end(char *str, int e_end)
{
	int	end_index;

	end_index = -2;
	if (str[0] == '\'')
		end_index = index_of(str + 1, "'", 1) + 2;
	else if (e_end > -1 && index_of(str, "'", 1) < e_end)
		end_index = get_arg_end(str, index_of(str + 1, "'", 2) + 2);
	else if (str[0] == '"')
		end_index = index_of(str + 1, "\"", 1) + 2;
	else if (e_end > -1 && index_of(str, "\"", 1) < e_end)
		end_index = get_arg_end(str, index_of(str + 1, "\"", 2) + 2);
	if (end_index != -2 && str[end_index] != ' ')
		end_index += index_of(str + end_index, " ", 1);
	return (end_index);
}

int	get_end_index(char *str, int e_end)
{
	int		end_index;
	char	**splitchar;
	int		cur;

	if (e_end == 0)
		return (0);
	splitchar = ft_split("&& || | << < >> >", ' ');
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

t_cmdlst	*parsing(char *command)
{
	t_cmdlst	*command_list;
	t_list		*args;

	args = NULL;
	if (!split_args(&args, command))
		return (NULL);
	if (!create_command_lst(&command_list, args))
	{
		lst_clear(&args);
		return (NULL);
	}
	lst_clear(&args);
	return (command_list);
}
