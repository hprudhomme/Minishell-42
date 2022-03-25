/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_multi_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:43:49 by ocartier          #+#    #+#             */
/*   Updated: 2022/03/25 15:18:32 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_sep(const char *s, char **seps)
{
	int	cur;

	cur = 0;
	if (!s[0])
		return (0);
	while (seps[cur])
	{
		if (ft_strncmp(s, seps[cur], ft_strlen(s)) == 0)
		{
			return (1);
		}
		cur++;
	}
	return (0);
}

int	start_with(const char *str, char *start)
{
	if (ft_strncmp(str, start, ft_strlen(start)) == 0)
		return (1);
	return (0);
}

static int	numwords(char const *s, char **seps)
{
	int	cur;
	int	se_cur;
	int	word_num;

	cur = 0;
	word_num = 0;
	while (s[cur] && !is_sep(s + cur, seps))
	{
		se_cur = 0;
		while (seps[se_cur])
		{
			if (start_with(s + cur, seps[se_cur]))
			{
				cur += ft_strlen(seps[se_cur]) - 1;
				break ;
			}
			else if (start_with(s + cur + 1, seps[se_cur])
				|| s[cur + ft_strlen(seps[se_cur])] == 0)
			{
				word_num++;
				break ;
			}
			se_cur++;
		}
		cur++;
	}
	return (word_num);
}

static char	*extract_word(const char *s, char *sep,
	int *end_cur, int *start_cur)
{
	char	*result;
	int		wordlen;

	result = NULL;
	printf("\n-> start %d, end %d, |%s|", *start_cur, *end_cur, s + *start_cur);
	if (start_with(s + *end_cur, sep))
	{
		printf("   ayo");
		*start_cur = *end_cur + ft_strlen(sep);

	}
	else
	{
		printf("  enbala");
		if (start_with(s + *end_cur + 1, sep) || !s[*end_cur + 1])
		{
			printf("ho");
			wordlen = *end_cur - *start_cur + 2;
			/*
			if (wordlen <= 0)
				wordlen = 1;
			*/
			//printf("\nstart %d, end %d, wordlen %d, %s", *start_cur, *end_cur, wordlen, s + *start_cur);
			result = malloc(sizeof(char) * wordlen);
			ft_strlcpy(result, (s + *start_cur), wordlen);
			*start_cur = *end_cur + ft_strlen(sep) + 1;
			*end_cur += ft_strlen(sep) - 1;
			if (result[0] == 0)
			{
				free(result);
				result = NULL;
			}
		}
	}
	return (result);
}

static int	split_words(char **result, char const *s, char **seps)
{
	int		start_cur;
	int		end_cur;
	int		se_cur;
	int		word;

	end_cur = 0;
	start_cur = 0;
	word = 0;
	while (s[end_cur])
	{
		se_cur = 0;
		while (seps[se_cur] && !is_sep(s + end_cur + 1, seps))
		{
			result[word] = extract_word(s, seps[se_cur], &end_cur, &start_cur);
			if (result[word])
			{
				printf("\n == %s", result[word]);
				word++;
				break ;
			}
			se_cur++;
		}
		end_cur++;
	}
	result[word] = 0;
	return (1);
}

char	**ft_split_multi_string(char const *s, char **seps)
{
	char	**result;

	if (!s || !seps)
		return (NULL);
	result = malloc(sizeof(char *) * (numwords(s, seps) + 1));
	printf("\nnumwords : %d\n", numwords(s, seps));
	if (!result)
		return (NULL);
	if (!split_words(result, s, seps))
	{
		free(result);
		return (NULL);
	}
	return (result);
}
