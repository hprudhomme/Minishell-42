/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 22:53:22 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/11 09:26:14 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	set_in_quotes(char c, int *in_quotes)
{
	int	cquotes;

	cquotes = *in_quotes;
	if (c == '\'')
	{
		if (cquotes == 0)
			*in_quotes = 1;
		else if (cquotes == 1)
			*in_quotes = 0;
	}
	if (c == '"')
	{
		if (cquotes == 0)
			*in_quotes = 2;
		else if (cquotes == 2)
			*in_quotes = 0;
	}
	return (cquotes);
}

int	get_future_arg_len(char *arg, char **env)
{
	int	cur;
	int	in_quotes;
	int	new_in_quotes;
	int	future_len;

	cur = 0;
	in_quotes = 0;
	new_in_quotes = 0;
	future_len = 0;
	while (arg[cur])
	{
		if (set_in_quotes(arg[cur], &in_quotes) == in_quotes)
			future_len++;
		if (in_quotes != 1 && arg[cur] == '$')
		{
			future_len += ft_strlen(get_env(arg + cur, env)) - 1;
			cur += get_envvar_size(arg + cur) - 1;
		}
		cur++;
	}
	return (future_len);
}

char	*replace_in_arg(char *arg, char **env)
{
	char	*n_arg;
	int		cur;
	int		in_quotes;
	int		new_in_quotes;
	int		n_cur;

	n_arg = ft_calloc(get_future_arg_len(arg, env) + 1, sizeof(char));
	if (!n_arg)
		return (NULL);
	cur = 0;
	n_cur = 0;
	in_quotes = 0;
	new_in_quotes = 0;
	while (arg[cur])
	{
		if (set_in_quotes(arg[cur], &in_quotes) == in_quotes)
			n_arg[n_cur++] = arg[cur];
		if (in_quotes != 1 && arg[cur] == '$')
		{
			n_cur += ft_strcat(n_arg + n_cur - 1, get_env(arg + cur, env)) - 1;
			cur += get_envvar_size(arg + cur) - 1;
		}
		cur++;
	}
	return (n_arg);
}

int	replace_quotes(char ***args, char **env)
{
	char	**new_args;
	int		cur;

	new_args = malloc(sizeof(char *) * (strarr_len(*args) + 1));
	if (!new_args)
		return (0);
	cur = 0;
	while ((*args)[cur])
	{
		new_args[cur] = replace_in_arg((*args)[cur], env);
		if (!new_args[cur])
			return (free_array_n(new_args, cur));
		cur++;
	}
	new_args[cur] = 0;
	strarr_free(*args);
	*args = new_args;
	return (1);
}
