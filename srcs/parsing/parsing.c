/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 09:08:48 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/03 13:08:23 by ocartier         ###   ########.fr       */
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
			return (test_index + quote_index + free_array(splitchar));
	}
	return (end_index + quote_index + free_array(splitchar));
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
	end_index = -2;
	if (str[0] == '\'')
		end_index = index_of(str + 1, "'", 1) + 2;
	else if (e_end > -1 && index_of(str, "'", 1) < e_end)
		end_index = get_arg_end(str, index_of(str + 1, "'", 2) + 2);
	else if (str[0] == '"')
		end_index = index_of(str + 1, "\"", 1) + 2;
	else if (e_end > -1 && index_of(str, "\"", 1) < e_end)
		end_index = get_arg_end(str, index_of(str + 1, "\"", 2) + 2);
	if (end_index == 0)
		return (free_array(splitchar));
	if (end_index != -2)
		return (end_index + free_array(splitchar));
	cur = -1;
	while (splitchar[++cur])
	{
		if ((e_end > -1 && index_of(str, splitchar[cur], 1) < e_end))
			return (index_of(str, splitchar[cur], 1) + free_array(splitchar));
		if (index_of(str, splitchar[cur], 1) == 0)
			return (ft_strlen(splitchar[cur]) + free_array(splitchar));
	}
	return (e_end + free_array(splitchar));
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
		if (cmd[cur] != ' ' && end_index + cur > ft_strlen(cmd))
			return (2);
		arg = ft_strldup(cmd + cur, end_index);
		if (!arg)
			return (lst_clear(args));
		if (!lst_append(args, arg))
			return (lst_clear(args));
		cur += ft_strlen(arg) - 1;
	}
	return (1);
}

t_command_list	*parsing(char *command)
{
	t_command_list	*command_list;
	t_list			*args;
	int				split_return;

	args = NULL;
	split_return = split_args(&args, command);
	if (!split_return)
		return (NULL);
	if (split_return == 2)
		printf("minishell > Error : missing quote");
	else
	{
		create_command_lst(&command_list, args); // TODO : can fail
		print_cmdlist(command_list);
	}
	ft_lstclear(&args, free);
	cmdlst_clear(&command_list);
	return (command_list);
}
