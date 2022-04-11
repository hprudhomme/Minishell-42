/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfiles.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:04:30 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/11 11:42:21 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Create a new outlst element with the given filename and action.
	It dulpicate the filename with ft_strdup
	Return 0 on malloc error
*/
t_outlst	*outlst_new(char *filename, int action)
{
	t_outlst	*new;

	new = malloc(sizeof(t_outlst));
	if (!new)
		return (0);
	new->filename = ft_strdup(filename);
	if (!new->filename)
	{
		free(new);
		return (0);
	}
	new->action = action;
	new->next = NULL;
	return (new);
}

/*
	Return a pointer to the last element of the given
	outfiles list
*/
t_outlst	*outlst_last(t_outlst *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

/*
	Create a new outlist element (using given filename and spe) using
	outlst_new.
	It convert the given spe to an int (> = OUT_WRITE, >> = OUT_APPEND).
	Then append it at the end of the given lst.
	Return 0 on malloc error
*/
int	outlst_append(t_outlst **lst, char *filename, char *spe)
{
	t_outlst	*new;
	t_outlst	*first;
	int			action;

	first = *lst;
	action = OUT_WRITE;
	if (ft_strlen(spe) == 2)
		action = OUT_APPEND;
	new = outlst_new(filename, action);
	if (!new)
		return (0);
	if (*lst)
		outlst_last(*lst)->next = new;
	else
		(*lst) = new;
	return (1);
}

/*
	Append the next arg of given args list to the given outfiles list.
	Return 0 on malloc error
	If the args->content is > or >>, it append args->next->content
	to the given list using outlst_append
*/
int	append_out_args(t_list **args, char *op, t_outlst **out)
{
	if (!(*args))
		return (1);
	if (ft_strlen(op) == ft_strlen((*args)->content)
		&& ft_strncmp((*args)->content, op, ft_strlen((*args)->content)) == 0)
	{
		*args = (*args)->next;
		if (*args && !outlst_append(out, (*args)->content, op))
			return (0);
		*args = (*args)->next;
	}
	return (1);
}
