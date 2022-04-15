/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 09:08:51 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/15 11:30:11 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Return the index of the n-th occurence of the
	given search in the given str
*/
int	index_of(char *str, char *search, int n)
{
	int	cur;

	cur = 0;
	while (str[cur])
	{
		if (ft_strncmp(str + cur, search, ft_strlen(search)) == 0)
			n--;
		if (n <= 0)
			return (cur);
		cur++;
	}
	return (cur);
}

/*
	Return NEXT_PIPE, NEXT_AND, NEXT_OR, NEXT_END or NEXT_CONTINUE
	depending of the value of str (|, &&, ||, ; or someting else)
*/
int	get_arg_type(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (NEXT_PIPE);
	if (!ft_strcmp(str, "&&"))
		return (NEXT_AND);
	if (!ft_strcmp(str, "||"))
		return (NEXT_OR);
	if (!ft_strcmp(str, ";"))
		return (NEXT_CONTINUE);
	return (NEXT_END);
}

/*
	Return 1 when str is a separator
	A separator can be : |, &, ||, &&, >, >>, <, <<, ;
*/
int	is_sep(char *str)
{
	if (get_arg_type(str) != 0)
		return (1);
	if (!ft_strcmp(str, ">"))
		return (1);
	if (!ft_strcmp(str, "<"))
		return (1);
	if (!ft_strcmp(str, "<<"))
		return (1);
	if (!ft_strcmp(str, ">>"))
		return (1);
	if (!ft_strcmp(str, "&"))
		return (1);
	if (!ft_strcmp(str, ";"))
		return (1);
	return (0);
}
