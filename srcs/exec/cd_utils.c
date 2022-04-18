/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 09:00:36 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/18 09:00:37 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**append_tab_2d(char **tab, char *s)
{
	int		i;
	char	**new;

	i = 0;
	new = (char **)malloc(sizeof(char *) * (tab_2d_len(tab) + 2));
	if (!new)
		return (NULL);
	while (tab[i])
	{
		new[i] = ft_strdup(tab[i]);
		i++;
	}
	new[i] = ft_strdup(s);
	i++;
	new[i] = NULL;
	free_tab_2d(tab);
	return (new);
}

char	**supp_last_elem_tab2d(char **tab)
{
	char	**new;
	int		len;
	int		i;

	i = 0;
	len = tab_2d_len(tab);
	new = (char **)malloc(sizeof(char *) * (tab_2d_len(tab)));
	if (!new)
		return (NULL);
	while (i < len - 1)
	{
		new[i] = ft_strdup(tab[i]);
		i++;
	}
	new[i] = NULL;
	free_tab_2d(tab);
	return (new);
}

/*
   return new pwd path
   */

char	*concat_path(char **tab, char *str)
{
	char	*s;
	char	*temp;
	int		i;

	i = 0;
	s = ft_strdup(str);
	temp = ft_strdup(s);
	free(s);
	while (tab[i])
	{
		s = ft_strjoin(temp, "/");
		free(temp);
		temp = ft_strdup(s);
		free(s);
		s = ft_strjoin(temp, tab[i]);
		free(temp);
		temp = ft_strdup(s);
		free(s);
		i++;
	}
	s = ft_strdup(temp);
	free(temp);
	return (s);
}
