/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 09:26:28 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/11 09:26:37 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env(char *env_name, char **env)
{
	int	e_cur;

	if (ft_strlen(env_name) >= 1
		&& env_name[0] == '$' && !ft_isalnum(env_name[1]))
		return ("$");
	e_cur = 0;
	while (env[e_cur])
	{
		if (!ft_strncmp(env[e_cur], env_name + 1,
				get_envvar_size(env_name) - 1))
			return (env[e_cur] + get_envvar_size(env_name));
		e_cur++;
	}
	return ("");
}

int	get_envvar_size(char *str)
{
	int	cur;

	cur = 0;
	while (str[cur] || (cur == 0 && str[cur] == '$'))
	{
		if (!ft_isalnum(str[cur]) && cur != 0)
			return (cur);
		cur++;
	}
	return (cur);
}
