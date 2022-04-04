/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hprudhom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:54:40 by hprudhom          #+#    #+#             */
/*   Updated: 2020/12/10 14:55:50 by hprudhom         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*sdest;
	unsigned char	*ssrc;

	if (dest == NULL && src == NULL)
		return (NULL);
	sdest = (unsigned char *)dest;
	ssrc = (unsigned char *)src;
	while (n--)
	{
		*sdest = *ssrc;
		sdest++;
		ssrc++;
	}
	return (dest);
}
