/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 09:08:51 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/11 11:28:00 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Same as ft_strdup, but with a size params to limit
	the length of the future string.
*/
char	*ft_strldup(const char *s1, size_t size)
{
	int		s1_len;
	char	*dup;

	s1_len = ft_strlen(s1);
	if (s1_len > size)
		s1_len = size;
	dup = (char *)malloc((s1_len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	dup[s1_len] = 0;
	while (--s1_len >= 0)
		dup[s1_len] = s1[s1_len];
	return (dup);
}

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
	Return NEXT_PIPE, NEXT_AND, NEXT_OR or NEXT_END
	depending of the value of str (|, &&, || or someting else)
*/
int	get_arg_type(char *str)
{
	if (ft_strncmp(str, "|", ft_strlen(str)) == 0)
		return (NEXT_PIPE);
	if (ft_strncmp(str, "&&", ft_strlen(str)) == 0)
		return (NEXT_AND);
	if (ft_strncmp(str, "||", ft_strlen(str)) == 0)
		return (NEXT_OR);
	return (NEXT_END);
}

/*
	Return 1 when str is a separator
	A separator can be : |, &, ||, &&, >, >>, < or <<
*/
int	is_sep(char *str)
{
	if (get_arg_type(str) != 0)
		return (1);
	if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
		return (1);
	if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
		return (1);
	if (ft_strncmp(str, "<<", ft_strlen(str)) == 0)
		return (1);
	if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
		return (1);
	if (ft_strncmp(str, "&", ft_strlen(str)) == 0)
		return (1);
	return (0);
}

/*
	Same as ft_strlcat but without the l
*/
int	ft_strcat(char *dst, char *src)
{
	int	cur;

	cur = 0;
	while (src[cur])
	{
		dst[cur] = src[cur];
		cur++;
	}
	return (cur);
}
