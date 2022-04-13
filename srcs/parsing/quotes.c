/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 22:53:22 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/13 07:12:27 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	in_quotes is a var that is equal to 1 when a single quote is openned,
	2 if a double quote is openned or 0 when quotes are closed.
	The function set given in_quotes to 0, 1 or 2 depending on the
	value of given char and the current in_quotes value.
	Return the previous value of in_quotes
*/
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

/*
	Calulate and return the len of the given arg when
	it's values (env vars) will be replaced.
*/
int	get_future_arg_len(char *arg, char **env, int last_exit)
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
			future_len += ft_strlen(get_env(arg + cur, env, last_exit)) - 1;
			cur += get_envvar_size(arg + cur) - 1;
		}
		cur++;
	}
	return (future_len);
}

/*
	Replace the env vars of the given arg and return the
	modified arg.
	lex stand for last exit
	Return NULL on malloc error
*/
char	*replace_in_arg(char *arg, char **env, int lex)
{
	char	*n_arg;
	int		cur;
	int		in_quotes;
	int		new_in_quotes;
	int		n_cur;

	n_arg = ft_calloc(get_future_arg_len(arg, env, lex) + 1, sizeof(char));
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
			n_cur += ft_strcat(n_arg + n_cur - 1, get_env(arg + cur, env, lex)) - 1;
			cur += get_envvar_size(arg + cur) - 1;
		}
		cur++;
	}
	return (n_arg);
}

/*
	Replace the env vars of every args in given array using replace_in_arg.
	It malloc a whole new array and duplicate every args (and replace env vars
	when needed), then it free the old arg array and set the args pointer
	to the new array.
	Return 0 on malloc error
*/
int	replace_quotes(char ***args, char **env, int last_exit)
{
	char	**new_args;
	int		cur;

	new_args = malloc(sizeof(char *) * (strarr_len(*args) + 1));
	if (!new_args)
		return (0);
	cur = 0;
	while ((*args)[cur])
	{
		new_args[cur] = replace_in_arg((*args)[cur], env, last_exit);
		if (!new_args[cur])
			return (free_array_n(new_args, cur));
		cur++;
	}
	new_args[cur] = 0;
	strarr_free(*args);
	*args = new_args;
	return (1);
}
