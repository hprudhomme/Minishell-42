/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 07:14:34 by ocartier          #+#    #+#             */
/*   Updated: 2022/03/28 10:21:20 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	lst_append(t_list **lst, char *str)
{
	t_list	*new;

	new = ft_lstnew(str);
	ft_lstadd_back(lst, new);
}
/*
void	cmdlst_append(t_list **lst, char *str)
{
	t_list	*new;

	new = ft_lstnew(str);
	ft_lstadd_back(lst, new);
}
*/

int	create_command_lst(t_command_list **command_list, t_list *args)
{
	char *arg;

	command_list = NULL;
	while (args && args->next)
	{
		if (ft_strncmp(args->content, "&&", ft_strlen(args->content)) == 0
			|| ft_strncmp(args->content, "||", ft_strlen(args->content)) == 0)
		{

			printf("-> %s + \n", args->next->content);
			args = args->next;
			while (args)
			{
				printf("%s ", args->content);
				args = args->next;
			}
		}
		args = args->next;
	}
	return (1);
}
