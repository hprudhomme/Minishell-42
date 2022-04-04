/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hprudhom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 16:15:29 by hprudhom          #+#    #+#             */
/*   Updated: 2020/12/10 16:15:32 by hprudhom         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	count_size(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_fill_dst(char *dst, int count, int i, long int n)
{
	while (count > i)
	{
		dst[--count] = (n % 10) + '0';
		n /= 10;
	}
	return (dst);
}

char	*ft_itoa(int num)
{	
	char		*dst;
	int			count;
	int			i;
	long int	n;

	n = num;
	if (n == -2147483648)
		n = 2147483648;
	count = count_size(n);
	i = 0;
	if (n < 0 || count == 0)
		count++;
	dst = ft_strnew(count);
	if (!dst)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		dst[0] = '-';
		i++;
	}
	dst = ft_fill_dst(dst, count, i, n);
	return (dst);
}
