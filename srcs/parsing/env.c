/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 09:26:28 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/13 08:11:45 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Return the env value (from given env) that correspond to the
	given env_name.
	Return $ if env_name is $
	Return "" (empty string) if env isn't found
	Return NULL on malloc error

	env_name can look likes this : $ENV_NAME@
*/
char	*get_env(char *env_name, char **env, int last_exit)
{
	int	e_cur;

	if (env_name[1] == '?')
		return (ft_itoa(last_exit));
	else if (env_name[1] == '$')
		return (ft_strdup("$"));
	else if (!ft_isalpha(env_name[1]))
		return (ft_strdup(""));
	e_cur = 0;
	while (env[e_cur])
	{
		if (!ft_strncmp(env[e_cur], env_name + 1,
				get_envvar_size(env_name) - 1))
			return (ft_strdup(env[e_cur] + get_envvar_size(env_name)));
		e_cur++;
	}
	return (ft_strdup(""));
}

/*
	Return the env name size that is at the start of the given str
	Read str (starting with the $) and stop when the character
	is not an authorized character in env name.
*/
int	get_envvar_size(char *str)
{
	int	cur;
	int	starts_with_num;

	if (ft_strncmp(str, "$?", ft_strlen(str)) == 0)
		return (2);
	starts_with_num = 0;
	if (!ft_isalpha(str[1]) && ft_isdigit(str[1]))
		starts_with_num = 1;
	cur = 0;
	while (str[cur] || (cur == 0 && str[cur] == '$'))
	{
		if (starts_with_num && ft_isalpha(str[cur]))
			return (cur);
		if (!ft_isalnum(str[cur]) && cur != 0)
			return (cur);
		cur++;
	}
	return (cur);
}
