/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 09:08:51 by ocartier          #+#    #+#             */
/*   Updated: 2022/03/28 12:13:33 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
