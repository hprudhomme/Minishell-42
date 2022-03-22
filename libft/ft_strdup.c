/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hprudhom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:20:18 by hprudhom          #+#    #+#             */
/*   Updated: 2020/12/10 15:20:54 by hprudhom         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;

	str = ft_strnew(ft_strlen(s));
	if (!str)
		return (NULL);
	ft_strcpy(str, s);
	return (str);
}
