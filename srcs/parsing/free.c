/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:31:51 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/06 19:47:02 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cmdlst_clear(t_cmdlst **lst)
{
	t_cmdlst	*next;

	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->command);
		strarr_free((*lst)->args);
		outlst_clear(&(*lst)->outfiles);
		strarr_free((*lst)->infiles);
		strarr_free((*lst)->heredocs);
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
	return (0);
}

int	outlst_clear(t_outlst **lst)
{
	t_outlst	*next;

	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->filename);
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
	return (0);
}

int	free_array_n(char **array, int n)
{
	while (n--)
		free(array[n]);
	free(array);
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
