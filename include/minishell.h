/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:57:56 by ocartier          #+#    #+#             */
/*   Updated: 2022/03/28 12:13:40 by ocartier         ###   ########.fr       */
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

// typedef struct s_list2_simple_cmd
// {
// 	int							nb;
// 	char			            **cmd;
// 	int							infile;
// 	int							outfile;
// 	char						*infile_name;
// 	char						*outfile_name;
// 	struct s_list2_simple_cmd	*next;
// }					t_list2_simple_cmd;

// typedef struct s_list2
// {
// 	 t_list2_simple_cmd *premier;
// }					t_list2;

// typedef struct s_mem
// {
// 	 t_list2_simple_cmd *premier;
// }					t_mem;



// char **str_to_wordtab(char * str);

// // list

// t_list2_simple_cmd	*ft_lstlast(t_list2_simple_cmd *lst);
// t_list2              *initialisation();
// t_list2_simple_cmd	*ft_lstnew(char **content);
// void ft_lstadd_back(t_list2 *list, t_list2_simple_cmd *new_elm);
// void				aff_list(t_list2 *list);
// int					list_len(t_list2 *list);
// void    			free_list(t_list2 *list);

// //	path

// char    *find_right_path(char **path_tab, char *cmd, char *right_path);
// char *find_path_redirect_file(char *pwd, char *actuel, char *redirect_path);

// //

// void     do_list_simple_cmd(char **tab_pipe_split, t_list2 *list);
// void    check_redirection(t_list2 *list);

// // exec

// void execute(t_list2 *list, char **path_tab);

// // utils

// int     tab_2d_len(char **tab);

// UTILS
char			**ft_split_multi_string(char const *s, char **seps);
char			*ft_strstr(char *str, char *to_find);
int				count_char(char *str, char c);
int				index_of(char *str, char *search, int n);

// PARSING
typedef struct s_command_list
{
	char					*command;
	char					**args;
	int						todo;
	char					*out_filename;
	struct s_command_list	*next;
}	t_command_list;
// parsing/lst.c
void			lst_append(t_list **lst, char *str);
void			print_list(t_list *lst);
int				create_command_lst(t_command_list **command_list, t_list *args);
// parsing/parsing.c
t_command_list	*parsing(char *command);
// parsing/quotes.c
int				rm_quotes(t_list **args);
// parsing/utils.c
char			*ft_strldup(const char *s1, size_t size);

#endif
