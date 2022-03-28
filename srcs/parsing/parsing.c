/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 09:08:48 by ocartier          #+#    #+#             */
/*   Updated: 2022/03/28 11:11:26 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_end_index(char *str, int existing_end)
{
	int		end_index;
	char	*uniqchar;
	int		cur;

	uniqchar = ft_strldup("|<>", 3);
	end_index = 0;
	if (str[0] == '\''
		|| (existing_end > -1 && index_of(str, '\'') < existing_end))
		end_index = index_of(str, '\'');
	else if (str[0] == '"'
		|| (existing_end > -1 && index_of(str, '"') < existing_end))
		end_index = index_of(str, '"');
	else if (str[0] == '&' || str[1] == '&'
		|| (existing_end > -1 && index_of(str, '&') < existing_end))
		end_index = index_of(str, '&');
	else if (str[0] == '|' && str[1] == '|'
		|| (existing_end > -1 && index_of(str, '|') < existing_end))
		end_index = index_of(str, '|');
	else
	{
		cur = -1;
		while (uniqchar[++cur])
			if (str[0] == uniqchar[cur]
				|| (existing_end > -1 && index_of(str, uniqchar[cur]) < existing_end))
				end_index = 0;
	}
	if (existing_end > -1 && !end_index)
		return (existing_end);
	return (end_index);
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
		if (cmd[cur] == '\'' || cmd[cur] == '"'
			|| cmd[cur] == '&' || cmd[cur] == '|' || cmd[cur] == '>')
			end_index = get_end_index(cmd + cur, -1) + 1;
		else
			end_index = get_end_index(cmd + cur, index_of(cmd + cur, ' '));
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
