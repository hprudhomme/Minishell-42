/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 09:01:46 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/18 09:01:47 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	tab_2d_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	free_tab_2d(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
}

int	is_in_env(char **my_env, char *s)
{
	int		i;
	char	**temp;

	i = 0;
	while (my_env[i])
	{
		temp = ft_split(my_env[i], '=');
		if (strcmp(temp[0], s) == 0)
			break ;
		free_tab_2d(temp);
		temp = NULL;
		i++;
	}
	if (temp)
		free_tab_2d(temp);
	if (i == tab_2d_len(my_env))
		return (0);
	return (1);
}

int	cmdlist_len(t_cmdlst *lst)
{
	int	cur;

	cur = 0;
	while (lst)
	{
		cur++;
		lst = lst->next;
	}
	return (cur);
}

int	outlst_len(t_outlst *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
