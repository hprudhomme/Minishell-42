/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hprudhom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:49:43 by hprudhom          #+#    #+#             */
/*   Updated: 2020/12/10 14:51:06 by hprudhom         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*sdest;
	unsigned char	*ssrc;

	sdest = (unsigned char *)dest;
	ssrc = (unsigned char *)src;
	while (n--)
	{
		*sdest = *ssrc;
		if (*ssrc == (unsigned char)c)
			return (sdest + 1);
		sdest++;
		ssrc++;
	}
	return (NULL);
}
