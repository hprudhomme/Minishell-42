/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 09:09:05 by ocartier          #+#    #+#             */
/*   Updated: 2022/03/29 08:19:40 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, char **argv)
{
	int		cur;
	char	*command;
	char	*temp;

	cur = 0;
	command = malloc(sizeof(char));
	command[0] = 0;
	while (cur++ < argc - 1)
	{
		temp = command;
		command = ft_strjoin(command, argv[cur]);
		free(temp);
	}
	parsing(command);
	free(command);
}
