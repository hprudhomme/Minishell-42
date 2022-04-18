/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 09:00:41 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/18 21:08:29 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	change path of pwd in env
	return env with new pwd
*/

char	**change_pwd(char **temp2, char **my_env)
{
	int		pwd_place;
	char	*new_pwd;
	char	**temp;
	int		i;

	i = 0;
	pwd_place = my_env_index_elem(my_env, "PWD");
	temp = (char **)malloc(sizeof(char *) * (tab_2d_len(my_env) + 1));
	if (!temp)
		return (NULL);
	pwd_place = my_env_index_elem(my_env, "PWD");
	new_pwd = concat_path(temp2, "PWD=");
	while (my_env[i])
	{
		if (i == pwd_place)
			temp[i] = ft_strdup(new_pwd);
		else
			temp[i] = ft_strdup(my_env[i]);
		i++;
	}
	temp[i] = NULL;
	free_tab_2d(my_env);
	free(new_pwd);
	return (temp);
}

/*
	change path of oldpwd in env
	return env with new oldpwd
*/

char	**change_oldpwd(char *pwd, char **my_env)
{
	char	*new_old_pwd;
	int		old_env_index;

	old_env_index = my_env_index_elem(my_env, "OLDPWD");
	new_old_pwd = ft_strjoin("OLDPWD=", pwd);
	free(my_env[old_env_index]);
	my_env[old_env_index] = ft_strdup(new_old_pwd);
	free(new_old_pwd);
	return (my_env);
}

char	**change_pwd_home(char **my_env)
{
	char	*new_pwd;
	int		pwd_index;
	char	*home;

	home = my_getenv(my_env, "HOME");
	pwd_index = my_env_index_elem(my_env, "PWD");
	new_pwd = ft_strjoin("PWD=", home);
	free(my_env[pwd_index]);
	my_env[pwd_index] = ft_strdup(new_pwd);
	free(new_pwd);
	free(home);
	return (my_env);
}
