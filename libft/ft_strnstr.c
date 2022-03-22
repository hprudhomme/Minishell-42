/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hprudhom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:32:29 by hprudhom          #+#    #+#             */
/*   Updated: 2020/12/11 17:51:33 by hprudhom         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	x;
	size_t	y;

	if (*little == '\0')
		return ((char *)big);
	x = 0;
	while (big[x] && x < n)
	{
		y = 0;
		while (big[x + y] == little[y] && x + y < n)
		{
			y++;
			if (little[y] == '\0')
				return ((char *)big + x);
		}
		x++;
	}
	return (NULL);
}
