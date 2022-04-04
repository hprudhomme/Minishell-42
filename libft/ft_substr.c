/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hprudhom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:40:05 by hprudhom          #+#    #+#             */
/*   Updated: 2020/12/17 19:14:32 by hprudhom         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int		x;
	char				*dst;
	size_t				len_s;

	if (!s)
		return (0);
	len_s = len;
	if (start > (unsigned int)ft_strlen(s) - 1)
	{
		dst = malloc(sizeof(char));
		if (!dst)
			return (NULL);
		dst[0] = '\0';
		return (dst);
	}
	if ((size_t)start + len > (size_t)ft_strlen(s))
		len_s = (size_t)ft_strlen(s) - (size_t)start;
	dst = malloc(sizeof(char) * (len_s + 1));
	if (!dst)
		return (NULL);
	x = 0;
	while (x < len_s)
		dst[x++] = s[start++];
	dst[x] = '\0';
	return (dst);
}
