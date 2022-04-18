/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 09:01:39 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/18 21:07:44 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*try_path(char **path_tab, char *cmd, char *right_path, int i)
{
	int	j;
	int	x;

	j = 0;
	x = 0;
	right_path = malloc(sizeof(char) * 150);
	while (path_tab[i][j])
		right_path[x++] = path_tab[i][j++];
	right_path[x] = '/';
	x++;
	j = 0;
	while (cmd[j])
		right_path[x++] = cmd[j++];
	right_path[x] = '\0';
	if (access(right_path, F_OK) == 0)
		return (right_path);
	free(right_path);
	return (NULL);
}

/*
	return a path used as first parameter of execve fct
*/

char	*find_exec_path(char **path_tab, char *cmd, char *right_path)
{
	int	i;
	int	j;
	int	x;

	if (cmd[0] == '.' || cmd[0] == '/')
		return (ft_strdup(cmd));
	if (!path_tab)
		return (NULL);
	i = 0;
	while (path_tab[i])
	{
		right_path = try_path(path_tab, cmd, right_path, i);
		if (right_path)
			return (right_path);
		i++;
	}
	return (NULL);
}

/*
	return redirect_file_path for outfiles
*/

char	*find_path_redirect_file(char *pwd, char *actuel, char *redirect_path)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	redirect_path = malloc(sizeof(char) * (ft_strlen(pwd)
				+ ft_strlen(actuel) + 3));
	if (!redirect_path)
		return (NULL);
	while (pwd[i])
		redirect_path[j++] = pwd[i++];
	redirect_path[j] = '/';
	j++;
	i = 0;
	while (actuel[i])
		redirect_path[j++] = actuel[i++];
	redirect_path[j] = '\0';
	return (redirect_path);
}
