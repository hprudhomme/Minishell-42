/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfiles.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:04:30 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/06 21:51:11 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

t_outlst	*outlst_last(t_outlst *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

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

int	append_out_args(t_list **args, t_cmdlst *new, char *op, t_outlst **out)
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
		return (2);
	}
	return (1);
}
