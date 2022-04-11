/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 09:26:28 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/11 09:46:55 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Return the env value (from given env) that correspond to the
	given env_name.
	Return $ if env_name is $
	Return "" (empty string) if env isn't found

	env_name can look likes this : $ENV_NAME@
*/
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

/*
	Return the env name size that is at the start of the given str
	Read str (starting with the $) and stop when the character
	is not an authorized character in env name.
*/
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
