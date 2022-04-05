/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 22:53:22 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/05 14:19:26 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env(char *env_name)
{
	if (ft_strlen(env_name) >= 1
		&& env_name[0] == '$' && !ft_isalnum(env_name[1]))
		return ("$");
	return ("monenv");
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

int	get_future_arg_len(char *arg)
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
		if (arg[cur] == '\'')
		{
			if (in_quotes == 0)
				new_in_quotes = 1;
			else if (in_quotes == 1)
				new_in_quotes = 0;
		}
		if (arg[cur] == '"')
		{
			if (in_quotes == 0)
				new_in_quotes = 2;
			else if (in_quotes == 2)
				new_in_quotes = 0;
		}
		if (new_in_quotes == in_quotes)
			future_len++;
		in_quotes = new_in_quotes;
		if (in_quotes != 1 && arg[cur] == '$')
		{
			future_len += ft_strlen(get_env(arg + cur)) - 1;
			cur += get_envvar_size(arg + cur) - 1;
		}
		cur++;
	}
	return (future_len);
}

char	*replace_in_arg(char *arg)
{
	char	*new_arg;
	int		cur;
	int		in_quotes;
	int		new_in_quotes;
	int		n_cur;

	new_arg = malloc(sizeof(char) * (get_future_arg_len(arg) + 1));
	cur = 0;
	n_cur = 0;
	in_quotes = 0;
	new_in_quotes = 0;
	while (arg[cur])
	{
		if (arg[cur] == '\'')
		{
			if (in_quotes == 0)
				new_in_quotes = 1;
			else if (in_quotes == 1)
				new_in_quotes = 0;
		}
		if (arg[cur] == '"')
		{
			if (in_quotes == 0)
				new_in_quotes = 2;
			else if (in_quotes == 2)
				new_in_quotes = 0;
		}
		if (new_in_quotes == in_quotes)
		{
			new_arg[n_cur] = arg[cur];
			n_cur++;
		}
		in_quotes = new_in_quotes;
		if (in_quotes != 1 && arg[cur] == '$')
		{
			n_cur--;
			char *env_val = get_env(arg + cur);
			int	ev_cur = 0;
			while (env_val[ev_cur])
			{
				new_arg[n_cur] = env_val[ev_cur];
				n_cur++;
				ev_cur++;
			}
			cur += get_envvar_size(arg + cur) - 1;
		}
		cur++;
	}
	new_arg[n_cur] = 0;
	return (new_arg);
}

int	replace_quotes(char ***args)
{
	char	**new_args;
	int		cur;

	new_args = malloc(sizeof(char *) * (strarr_len(*args) + 1));
	if (!new_args)
		return (0);
	cur = 0;
	while ((*args)[cur])
	{
		new_args[cur] = replace_in_arg((*args)[cur]);
		if (!new_args[cur])
			return (free_array_n(new_args, cur));
		cur++;
	}
	new_args[cur] = 0;
	strarr_free(*args);
	*args = new_args;
	return (1);
}
