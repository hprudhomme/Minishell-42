/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:31:53 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/06 19:50:34 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

t_cmdlst	*cmdlst_last(t_cmdlst *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

int	append_in_args(t_list **args, t_cmdlst *new, char *op, char ***array)
{
	if (ft_strlen(op) == ft_strlen((*args)->content)
		&& ft_strncmp((*args)->content, op, ft_strlen((*args)->content)) == 0)
	{
		*args = (*args)->next;
		if (*args && !strarr_append(array, (*args)->content))
			return (0);
		if ((*args)->next)
			*args = (*args)->next;
		return (2);
	}
	return (1);
}

int	cmdlist_append_args(t_list **args, t_cmdlst *new)
{
	int		ret;

	while (*args && !get_arg_type((*args)->content))
	{
		if (!append_out_args(args, new, ">", &(new->outfiles)))
			return (0);
		else if (!append_in_args(args, new, "<", &(new->infiles)))
			return (0);
		else if (!append_out_args(args, new, ">>", &(new->outfiles)))
			return (0);
		else if (!append_in_args(args, new, "<<", &(new->heredocs)))
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

int	create_command_lst(t_cmdlst **command_list, t_list *args)
{
	t_cmdlst	*new;

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
