/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 09:09:05 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/06 20:07:20 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_list(t_list *lst)
{
	int	cur;

	cur = 0;
	printf("\nList : \n");
	while (lst)
	{
		cur++;
		printf("  - |%s|\n", (char *)lst->content);
		lst = lst->next;
	}
}

void	print_cmdlist(t_cmdlst *lst)
{
	int			cur;
	int			a_cur;
	t_outlst	*out_it;

	cur = 0;
	printf("\nCommands List : \n");
	while (lst)
	{
		cur++;
		printf("  -> %s\n     args: [", lst->command);
		a_cur = 0;
		while (lst->args && lst->args[a_cur])
		{
			printf("\"%s\", ", lst->args[a_cur]);
			a_cur++;
		}
		printf("]\n");
		if (lst->todo_next == NEXT_OR)
			printf("     -> Next : OR\n");
		else if (lst->todo_next == NEXT_AND)
			printf("     -> Next : AND\n");
		else if (lst->todo_next == NEXT_PIPE)
			printf("     -> Next : PIPE\n");
		else
			printf("     -> Next : END\n");
		printf("     outfiles: [");
		out_it = lst->outfiles;
		while (out_it)
		{
			if (out_it->action == OUT_APPEND)
				printf("append : \"%s\", ", out_it->filename);
			if (out_it->action == OUT_WRITE)
				printf("write : \"%s\", ", out_it->filename);
			out_it = out_it->next;
		}
		printf("]\n");
		printf("     infiles: [");
		a_cur = 0;
		while (lst->infiles && lst->infiles[a_cur])
		{
			printf("\"%s\", ", lst->infiles[a_cur]);
			a_cur++;
		}
		printf("]\n");
		printf("     heredocs: [");
		a_cur = 0;
		while (lst->heredocs && lst->heredocs[a_cur])
		{
			printf("\"%s\", ", lst->heredocs[a_cur]);
			a_cur++;
		}
		printf("]\n");
		lst = lst->next;
	}
}
/*
int	main(int argc, char **argv)
{
	int			cur;
	char		*command;
	char		*temp;
	t_cmdlst	*command_list;

	cur = 0;
	command = malloc(sizeof(char));
	command[0] = 0;
	while (cur++ < argc - 1)
	{
		temp = command;
		command = ft_strjoin(command, argv[cur]);
		free(temp);
	}
	command_list = parsing(command); // can return null on error (syntax error, malloc error...)
	if (command_list)
	{
		replace_quotes(&(command_list->args)); // can return 0 (malloc error)
		print_cmdlist(command_list);
		cmdlst_clear(&command_list);
	}
	free(command);
}
*/
