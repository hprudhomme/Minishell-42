/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:09:07 by ocartier          #+#    #+#             */
/*   Updated: 2022/03/25 14:09:18 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	cur;
	int	cur2;

	cur = 0;
	if (ft_strlen(to_find) == 0)
		return (str);
	while (str[cur] != 0)
	{
		cur2 = 0;
		while (to_find[cur2] != 0)
		{
			if (str[cur + cur2] != to_find[cur2])
				break ;
			cur2++;
		}
		if (cur2 == ft_strlen(to_find))
			return (str + cur);
		cur++;
	}
	return (0);
}
