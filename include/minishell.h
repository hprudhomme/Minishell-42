/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:57:56 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/05 14:51:33 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include<readline/readline.h>
# include<readline/history.h>

# include "../libft/include/libft.h"

# define NEXT_END		0
# define NEXT_PIPE		1
# define NEXT_AND		2
# define NEXT_OR		3

typedef struct s_cmdlst
{
	char			*command;
	char			**args;
	char			**infiles;
	char			**write_in;
	char			**append_in;
	char			**heredocs;
	int				todo_next;
	struct s_cmdlst	*next;
}	t_cmdlst;
// parsing/cmdlst.c
t_cmdlst	*cmdlst_new(void);
t_cmdlst	*cmdlst_last(t_cmdlst *lst);
int			append_args(t_list **args, t_cmdlst *new, char *op, char ***array);
int			cmdlist_append_args(t_list **args, t_cmdlst *new);
int			create_command_lst(t_cmdlst **command_list, t_list *args);
// parsing/free.c
int			cmdlst_clear(t_cmdlst **lst);
int			free_array_n(char **array, int n);
int			lst_clear(t_list **lst);
int			strarr_free(char **array);
// parsing/lst.c
int			lst_append(t_list **lst, char *str);
int			strarr_len(char **array);
int			strarr_append(char ***array, char *str);
// parsing/parsing.c
int			get_arg_end(char *str, int quote_index);
int			get_quotes_end(char *str, int e_end);
int			get_end_index(char *str, int e_end);
int			split_args(t_list **args, char *cmd);
t_cmdlst	*parsing(char *command);
// parsing/quotes.c
int			replace_quotes(char ***args);
// parsing/utils.c
char		*ft_strldup(const char *s1, size_t size);
int			index_of(char *str, char *search, int n);
int			get_arg_type(char *str);
int			is_not_sep(char *str);

// parsing/test.c
void		print_list(t_list *lst);
void		print_cmdlist(t_cmdlst *lst);

#endif
