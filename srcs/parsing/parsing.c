/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 09:08:48 by ocartier          #+#    #+#             */
/*   Updated: 2022/03/25 23:34:49 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
void	array_free(char **array)
{
	int	cur;

	cur = 0;
	while (array[cur])
	{
		free(array[cur]);
		cur++;
	}
	free(array);
}

int	array_len(char **array)
{
	int	cur;

	cur = 0;
	while (array[cur])
		cur++;
	return (cur);
}

void	print_array(char **array)
{
	int	cur;

	cur = 0;
	printf("\nArray :\n");
	while (array[cur])
	{
		printf("  - %s\n", array[cur]);
		cur++;
	}
}

void	append_array(char ***array, char *str)
{
	char	**old;
	int		cur;

	old = *array;
	*array = malloc(sizeof(char) * (array_len(old) + 2));
	cur = 0;
	while (old[cur])
	{
		(*array)[cur] = ft_strdup(old[cur]);
		cur++;
	}
	(*array)[cur] = ft_strdup(str);
	(*array)[cur + 1] = 0;
	//free(old);
	array_free(old);
}

void	merge_array_elem(char ***array, int i)
{
	char	**merged;
	int		cur;

	merged = malloc(sizeof(char));
	merged[0] = 0;
	cur = 0;

	while ((*array)[cur])
	{
		append_array(&merged, "ok");
		cur++;
	}

	//array_free(*array);
	//free(*array);
	*array = merged;
}
*/

void	free_array(char **array)
{
	int	cur;

	cur = 0;
	while (array[cur])
	{
		free(array[cur]);
		cur++;
	}
	free(array);
}

void	print_list(t_list *lst)
{
	int	cur;

	cur = 0;
	printf("\nList : \n");
	while (lst)
	{
		cur++;
		printf("  - |%s|\n", (char *)lst->content);
		lst = lst->next;
	}
}

t_list	*array_to_list(char **array)
{
	t_list	*list;
	t_list	*new;
	int		cur;

	cur = 0;
	list = NULL;
	while (array[cur])
	{
		new = ft_lstnew(ft_strdup(array[cur]));
		ft_lstadd_back(&list, new);
		cur++;
	}
	return (list);
}

void	merge_list_items(t_list	**lst, int index)
{
	t_list	*start;
	int		cur;
	char	*new_content;
	t_list	*merged_elem;

	start = *lst;
	cur = 0;
	while (*lst && (*lst)->next)
	{
		if (cur == index)
		{
			merged_elem = (*lst)->next;
			new_content = ft_strjoin((*lst)->content, merged_elem->content);
			free((*lst)->content);
			(*lst)->content = new_content;
			(*lst)->next = merged_elem->next;
			free(merged_elem->content);
			free(merged_elem);
			break ;
		}
		cur++;
		*lst = (*lst)->next;
	}
	*lst = start;
}

int	index_of(char *str, char c)
{
	int	cur;

	cur = 0;
	while (str[cur])
	{
		if (str[cur] == c && cur != 0)
			return (cur);
		cur++;
	}
	return (cur);
}

void	lst_append(t_list **lst, char *str)
{
	t_list	*new;

	new = ft_lstnew(str);
	ft_lstadd_back(lst, new);
}

int split_args(t_list **args, char *command)
{
	int		cur;
	char	*arg;
	int		end_index;

	cur = -1;
	while (command[++cur])
	{
		if (command[cur] == ' ')
			continue ;
		if (command[cur] == '\'')
			end_index = index_of(command + cur, '\'') + 1;
		else if (command[cur] == '"')
			end_index = index_of(command + cur, '"') + 1;
		else
		{
			end_index = index_of(command + cur, ' ');
			if (index_of(command + cur, '"') < end_index)
				end_index = index_of(command + cur, '"') - 1;
			if (index_of(command + cur, '\'') < end_index)
				end_index = index_of(command + cur, '\'') - 1;
		}
		if (command[cur] != ' ' && end_index + cur > ft_strlen(command))
			return (2);
		arg = ft_strldup(command + cur, end_index);
		lst_append(args, arg);
		cur += ft_strlen(arg);
	}
	return (1);
}

t_command_list	*parsing(char *command)
{
	t_command_list	*command_list;
	char			**commands_array;
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
		printf("\n REPLACE QUOTES\n");
		rm_quotes(&args);
		print_list(args);
	}
	ft_lstclear(&args, free);
	return (command_list);
}
