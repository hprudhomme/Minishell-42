/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 09:08:48 by ocartier          #+#    #+#             */
/*   Updated: 2022/03/28 13:28:50 by ocartier         ###   ########.fr       */
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
	end_index = index_of(str + quote_index, " ", 1);
	cur = -1;
	while (splitchar[++cur])
	{
		test_index = index_of(str + quote_index, splitchar[cur], 1);
		if (test_index < end_index)
			return (test_index + quote_index);
	}
	return (end_index + quote_index);
}

int	get_end_index(char *str, int existing_end)
{
	int		end_index;
	char	**splitchar;
	int		cur;

	splitchar = ft_split("&& || | << < >> >", ' ');
	end_index = 0;
	if (str[0] == '\'')
		return (index_of(str + 1, "'", 1) + 2);
	if (existing_end > -1 && index_of(str, "'", 1) < existing_end)
		return (get_arg_end(str, index_of(str + 1, "'", 2) + 2));
	if (str[0] == '"')
		return (index_of(str + 1, "\"", 1) + 2);
	if (existing_end > -1 && index_of(str, "\"", 1) < existing_end)
		return (get_arg_end(str, index_of(str + 1, "\"", 2) + 2));
	cur = -1;
	while (splitchar[++cur])
	{
		if ((existing_end > -1
				&& index_of(str, splitchar[cur], 1) < existing_end))
			return (index_of(str, splitchar[cur], 1));
		if (index_of(str, splitchar[cur], 1) == 0)
			return (ft_strlen(splitchar[cur]));
	}
	return (existing_end);
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
		if (cmd[cur] != ' ' && end_index + cur > ft_strlen(cmd))
			return (2);
		arg = ft_strldup(cmd + cur, end_index);
		lst_append(args, arg);
		cur += ft_strlen(arg) - 1;
	}
	return (1);
}

t_command_list	*parsing(char *command)
{
	t_command_list	*command_list;
	t_list			*args;

	args = NULL;
	printf("Input command : %s\n", command);
	printf("\n GET ARGS\n");
	int split_return = split_args(&args, command);
	if (split_return == 2)
		printf("minishell > Error : missing quote");
	else
	{
		print_list(args);
		printf("\n COMMAND LIST\n");
		create_command_lst(&command_list, args);
		//print_list(args);
	}
	ft_lstclear(&args, free);
	return (command_list);
}
