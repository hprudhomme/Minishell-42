/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 07:14:34 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/01 17:16:44 by ocartier         ###   ########.fr       */
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

void	print_cmdlist(t_command_list *lst)
{
	int	cur;
	int	a_cur;

	cur = 0;
	printf("\nCommands List : \n");
	while (lst)
	{
		cur++;
		printf("  -> %s\n     args: [", lst->command);
		a_cur = 0;
		while (lst->args && lst->args[a_cur])
		{
			printf("\"%s\",", lst->args[a_cur]);
			a_cur++;
		}
		printf("]\n");
		if (lst->todo_next == NEXT_OR)
			printf("     -> Next : OR\n");
		else if (lst->todo_next == NEXT_AND)
			printf("     -> Next : AND\n");
		else if (lst->todo_next == NEXT_PIPE)
			printf("     -> Next : PIPE\n");
		else
			printf("     -> Next : END\n");
		printf("     outfiles: [");
		a_cur = 0;
		while (lst->outfiles && lst->outfiles[a_cur])
		{
			printf("\"%s\",", lst->outfiles[a_cur]);
			a_cur++;
		}
		printf("]\n");
		printf("     infiles: [");
		a_cur = 0;
		while (lst->infiles && lst->infiles[a_cur])
		{
			printf("\"%s\",", lst->infiles[a_cur]);
			a_cur++;
		}
		printf("]\n");
		lst = lst->next;
	}
}

void	lst_append(t_list **lst, char *str)
{
	t_list	*new;

	new = ft_lstnew(str); // TODO : can fail
	ft_lstadd_back(lst, new);
}

t_command_list	*cmdlst_last(t_command_list *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

int	strarr_free(char **array)
{
	int	cur;

	cur = -1;
	if (array)
	{
		while (array[++cur])
			free(array[cur]);
		free(array);
	}
	return (0);
}

int	lst_clear(t_list **lst)
{
	t_list	*next;

	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
	return (0);
}


void	cmdlst_clear(t_command_list **lst)
{
	t_command_list	*next;

	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->command);
		strarr_free((*lst)->args);
		strarr_free((*lst)->outfiles);
		strarr_free((*lst)->infiles);
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
}

int	strarr_len(char **array)
{
	int	cur;

	cur = 0;
	if (array)
		while (array[cur])
			cur++;
	return (cur);
}

int	strarr_append(char ***array, char *str)
{
	char	**new;
	int		new_len;
	int		cur;

	new_len = strarr_len(*array) + 1;
	new = malloc(sizeof(char *) * (new_len + 1)); // TODO : can fail
	cur = 0;
	while ((*array) && (*array)[cur])
	{
		new[cur] = ft_strdup((*array)[cur]); // TODO : can fail
		cur++;
	}
	new[cur] = ft_strdup(str); // TODO : can fail
	cur++;
	new[cur] = 0;
	strarr_free(*array);
	*array = new;
	return (1);
}

int get_arg_type(char *str)
{
	if (ft_strncmp(str, "|", ft_strlen(str)) == 0)
		return (NEXT_PIPE);
	if (ft_strncmp(str, "&&", ft_strlen(str)) == 0)
		return (NEXT_AND);
	if (ft_strncmp(str, "||", ft_strlen(str)) == 0)
		return (NEXT_OR);
	return (NEXT_END);
}

int	create_command_lst(t_command_list **command_list, t_list *args)
{
	t_command_list	*list;
	t_command_list	*new;

	*command_list = NULL;
	while (args && args->next)
	{
		new = malloc(sizeof(t_command_list)); // TODO : can fail
		new->command = ft_strdup(args->content); // TODO : can fail
		new->next = NULL;
		new->todo_next = 0;
		new->args = NULL;
		new->infiles = NULL;
		new->outfiles = NULL;
		// ARGS
		strarr_append(&(new->args), args->content); // TODO : can fail
		args = args->next;
		while (args && !get_arg_type(args->content))
		{
			// OUTFILES
			if (ft_strncmp(args->content, ">", ft_strlen(args->content)) == 0)
			{
				args = args->next;
				if (args)
					strarr_append(&(new->outfiles), args->content); // TODO : can fail
				args = args->next;
				continue ;
			}
			// INFILES
			if (ft_strncmp(args->content, "<", ft_strlen(args->content)) == 0)
			{
				args = args->next;
				if (args)
					strarr_append(&(new->infiles), args->content); // TODO : can fail
				args = args->next;
				continue ;
			}
			strarr_append(&(new->args), args->content); // TODO : can fail
			args = args->next;
		}
		// TODO NEXT
		if (args)
			new->todo_next = get_arg_type(args->content);
		else
			new->todo_next = NEXT_END;
		// ADD TO LIST
		if (*command_list)
			cmdlst_last(*command_list)->next = new;
		else
			*command_list = new;
		if (args)
			args = args->next;
	}
	return (1);
}
