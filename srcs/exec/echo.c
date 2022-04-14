#include "../../include/minishell.h"

void	echo_arg(char *str)
{
	int	cur;

	cur = -1;
	while (str[++cur])
	{
		if (ft_strncmp(str + cur, "\\n", 2) == 0)
		{
			ft_putchar_fd('\n', 1);
			cur++;
		}
		else
			ft_putchar_fd(str[cur], 1);
	}
}

int	ft_echo(char **s, t_mem *mem)
{
	char	*tmp;
	int		i;
	int		has_n;

	i = 0;
	has_n = 0;
	if (s[1] && ft_strncmp(s[1], "-n", 2) == 0)
		has_n = 1;
	if (has_n)
		i++;
	while (s[++i])
	{
		if ((!has_n && i > 1) || (has_n && i > 2))
			ft_putchar_fd(' ', 1);
		echo_arg(s[1]);
	}
	if (!has_n || strarr_len(s) == 1)
		ft_putchar_fd('\n', 1);
	mem->exit_statue = 0;
	return (1);
}
