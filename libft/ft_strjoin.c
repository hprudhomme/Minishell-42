/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hprudhom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:21:21 by hprudhom          #+#    #+#             */
/*   Updated: 2020/12/16 16:56:53 by hprudhom         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		x;
	int		y;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	x = 0;
	y = 0;
	while (s1[x])
	{
		str[y] = s1[x];
		y++;
		x++;
	}
	x = 0;
	while (s2[x])
	{
		str[y] = s2[x];
		y++;
		x++;
	}
	str[y] = '\0';
	return (str);
}
