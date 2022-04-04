/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hprudhom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:36:09 by hprudhom          #+#    #+#             */
/*   Updated: 2020/12/17 19:28:29 by hprudhom         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	istrim(char c, char const *set)
{
	int	x;

	x = 0;
	while (set[x])
	{
		if (set[x] == c)
			return (1);
		x++;
	}
	return (0);
}

static int	start_trim(char const *s1, char const *set)
{
	int	x;

	x = 0;
	while (s1[x] && istrim(s1[x], set))
		x++;
	return (x);
}

static int	end_trim(char const *s1, char const *set)
{
	int	x;

	x = ft_strlen(s1) - 1;
	while (x >= 0 && istrim(s1[x], set))
		x--;
	return (x);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start__trim;
	int		end__trim;
	int		x;
	char	*str;

	start__trim = start_trim(s1, set);
	end__trim = end_trim(s1, set);
	if (start__trim >= end__trim)
	{
		str = malloc(sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	str = malloc(sizeof(char) * (end__trim - start__trim) + 1 + 1);
	if (!str)
		return (NULL);
	x = 0;
	while (start__trim <= end__trim)
		str[x++] = s1[start__trim++];
	str[x] = '\0';
	return (str);
}
