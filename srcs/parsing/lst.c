/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 07:14:34 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/04 16:36:52 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	lst_append(t_list **lst, char *str)
{
	t_list	*new;

	new = ft_lstnew(str);
	if (!new)
		return (lst_clear(&new));
	ft_lstadd_back(lst, new);
	return (1);
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
