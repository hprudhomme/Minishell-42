/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:31:53 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/20 11:40:22 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Create a new empty cmdlst element
	Return 0 on malloc error
*/
t_cmdlst	*cmdlst_new(void)
{
	t_cmdlst	*new;

	new = malloc(sizeof(t_cmdlst));
	if (!new)
		return (0);
	new->command = NULL;
	new->next = NULL;
	new->todo_next = NEXT_END;
	new->args = NULL;
	new->infiles = NULL;
	new->outfiles = NULL;
	new->heredocs = NULL;
	return (new);
}

/*
	Return a pointer to the last element of the given
	command list
*/
t_cmdlst	*cmdlst_last(t_cmdlst *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

/*
	Append the next arg of given args list to the given array.
	Return 0 on malloc error
	array can be infiles or heredoc.
	If the args->content is < or <<, it append args->next->content
	to the given array using strarr_append
*/
int	append_in_args(t_list **args, char *op, char ***array)
{
	if (!(*args))
		return (1);
	if (ft_strlen(op) == ft_strlen((*args)->content)
		&& !strcmp_len((*args)->content, op))
	{
		*args = (*args)->next;
		if (*args && !strarr_append(array, (*args)->content))
			return (0);
		*args = (*args)->next;
	}
	return (1);
}

/*
	Append args->content to the right array / list
	Return 0 on malloc error
	If args->content is equal to > or >>
		It append args->next->content to the outfiles list
		-> using append_out_args
	If args->content is equal to <
		It append args->next->content to the infiles array
		-> using append_in_args
	If args->content is equal to <<
		It append args->next->content to the heredocs array
		-> using append_in_args
	Else
		It append args->content to the args array
		-> using strarr_append
*/
int	cmdlist_append_args(t_list **args, t_cmdlst *new)
{
	while (*args && !get_arg_type((*args)->content))
	{
		if (!append_out_args(args, ">", &(new->outfiles)))
			return (0);
		else if (!append_in_args(args, "<", &(new->infiles)))
			return (0);
		else if (!append_out_args(args, ">>", &(new->outfiles)))
			return (0);
		else if (!append_in_args(args, "<<", &(new->heredocs)))
			return (0);
		if ((*args) && !is_sep((*args)->content))
		{
			if (!strarr_append(&(new->args), (*args)->content))
				return (0);
			*args = (*args)->next;
		}
	}
	return (1);
}

/*
	Create a command list from an args list
	Return 0 on malloc error
*/
int	create_command_lst(t_cmdlst **command_list, t_list *args)
{
	t_cmdlst	*new;

	*command_list = NULL;
	while (args && !get_arg_type(args->content))
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
