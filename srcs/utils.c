/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 09:00:29 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/18 09:44:49 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	Return a NULL (void *)
	The given int is ignored
*/
void	*nil(int i)
{
	(void)i;
	return (NULL);
}

/*
	Free the given str and return 0
*/
int	free_str(char *str)
{
	free(str);
	return (0);
}

/*
	Return 1 if the given str contains only the given char
*/
int	contains_only(char *str, char c)
{
	int	cur;

	cur = -1;
	while (str[++cur])
		if (str[cur] != c)
			return (0);
	return (1);
}

/*
	Used in parsing/quotes.c, copy the given var_val at the end
	of the given n_arg and update cursor
	(Only useful to respect the norme)
*/
int	replace_var(char *var_val, char *n_arg, int *n_cur)
{
	if (!var_val)
		return (free_str(n_arg));
	*n_cur += ft_strcat(n_arg + (*n_cur) - 1, var_val) - 1;
	free(var_val);
	return (1);
}
