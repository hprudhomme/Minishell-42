/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 07:14:34 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/04 14:28:21 by ocartier         ###   ########.fr       */
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
		printf("     outfiles (write): [");
		a_cur = 0;
		while (lst->write_in && lst->write_in[a_cur])
		{
			printf("\"%s\",", lst->write_in[a_cur]);
			a_cur++;
		}
		printf("]\n");
		printf("     outfiles (append): [");
		a_cur = 0;
		while (lst->append_in && lst->append_in[a_cur])
		{
			printf("\"%s\",", lst->append_in[a_cur]);
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
		printf("     heredocs: [");
		a_cur = 0;
		while (lst->heredocs && lst->heredocs[a_cur])
		{
			printf("\"%s\",", lst->heredocs[a_cur]);
			a_cur++;
		}
		printf("]\n");
		lst = lst->next;
	}
}

int	lst_append(t_list **lst, char *str)
{
	t_list	*new;

	new = ft_lstnew(str);
	if (!new)
		return (lst_clear(&new));
	ft_lstadd_back(lst, new);
	return (1);
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


int	cmdlst_clear(t_command_list **lst)
{
	t_command_list	*next;

	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->command);
		strarr_free((*lst)->args);
		strarr_free((*lst)->write_in);
		strarr_free((*lst)->append_in);
		strarr_free((*lst)->infiles);
		strarr_free((*lst)->heredocs);
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
	return (0);
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

int	free_array_n(char **array, int n)
{
	while (n--)
		free(array[n]);
	free(array);
	return (0);
}

int	strarr_append(char ***array, char *str)
{
	char	**new;
	int		new_len;
	int		cur;

	new_len = strarr_len(*array) + 1;
	new = malloc(sizeof(char *) * (new_len + 1));
	if (!new)
		return (0);
	cur = 0;
	while ((*array) && (*array)[cur])
	{
		new[cur] = ft_strdup((*array)[cur]);
		if (!new[cur])
			return (free_array_n(new, cur));
		cur++;
	}
	new[cur] = ft_strdup(str);
	if (!new[cur])
		return (free_array_n(new, cur));
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

t_command_list	*cmdlst_new()
{
	t_command_list	*new;

	new = malloc(sizeof(t_command_list));
	if (!new)
		return (0);
	new->command = NULL;
	new->next = NULL;
	new->todo_next = NEXT_END;
	new->args = NULL;
	new->infiles = NULL;
	new->write_in = NULL;
	new->append_in = NULL;
	new->heredocs = NULL;
	return (new);
}

int	append_args(t_list **args, t_command_list *new, char *op, char ***array)
{
	if (ft_strncmp((*args)->content, op, ft_strlen((*args)->content)) == 0)
	{
		*args = (*args)->next;
		if (*args && !strarr_append(array, (*args)->content))
			return (0);
		*args = (*args)->next;
		return (2);
	}
	return (1);
}

int	cmdlist_append_args(t_list **args, t_command_list *new)
{
	int		ret;

	while (*args && !get_arg_type((*args)->content))
	{
		ret = append_args(args, new, ">", &(new->write_in));
		if (!ret)
			return (0);
		else if (ret == 2)
			continue ;
		ret = append_args(args, new, "<", &(new->infiles));
		if (!ret)
			return (0);
		else if (ret == 2)
			continue ;
		ret = append_args(args, new, ">>", &(new->append_in));
		if (!ret)
			return (0);
		else if (ret == 2)
			continue ;
		ret = append_args(args, new, "<<", &(new->heredocs));
		if (!ret)
			return (0);
		else if (ret == 2)
			continue ;
		if (!strarr_append(&(new->args), (*args)->content))
			return (0);
		*args = (*args)->next;
	}
	return (1);
}

int	create_command_lst(t_command_list **command_list, t_list *args)
{
	t_command_list	*new;

	*command_list = NULL;
	while (args)
	{
		new = cmdlst_new();
		if (!new)
			return (cmdlst_clear(command_list));
		if (*command_list)
			cmdlst_last(*command_list)->next = new;
		else
			*command_list = new;
		new->command = ft_strdup(args->content);
		if (!new->command)
			return (cmdlst_clear(command_list));
		if (!cmdlist_append_args(&args, new))
			return (cmdlst_clear(command_list));
		if (args)
			new->todo_next = get_arg_type(args->content);
		if (args)
			args = args->next;
	}
	return (1);
}
