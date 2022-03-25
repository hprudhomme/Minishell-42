/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 22:53:22 by ocartier          #+#    #+#             */
/*   Updated: 2022/03/25 23:34:13 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	replace_env(char **str)
{
	char	*replaced;

	replaced = ft_strdup(".il y a un env à remplacer.");
	free(*str);
	*str = replaced;
	return (1);
}

int	rm_quotes(t_list **args)
{
	t_list	*lst;
	char	*arg;
	int		to_clear;

	lst = *args;
	while (lst)
	{
		to_clear = 0;
		arg = (char *)lst->content;
		if (arg[0] == '\'' || arg[0] == '"')
			to_clear = 1;
		if (arg[0] == '"')
			replace_env(&arg);
		if (to_clear)
		{
			lst->content = ft_strldup(arg + 1, ft_strlen(arg) - 2);
			free(arg);
		}
		lst = lst->next;
	}
	return (1);
}
