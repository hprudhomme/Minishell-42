/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 22:00:10 by ocartier          #+#    #+#             */
/*   Updated: 2022/03/25 22:02:12 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	count_char(char *str, char c)
{
	int	cur;
	int	count;

	cur = 0;
	count = 0;
	while (str[cur])
	{
		if (str[cur] == c)
			count++;
		cur++;
	}
	return (count);
}
