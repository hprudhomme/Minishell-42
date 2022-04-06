/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:57:56 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/06 19:51:35 by ocartier         ###   ########.fr       */
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

/*
	EXEC
*/
typedef struct s_list2_simple_cmd
{
	int							nb;
	char			            **cmd;
	int							infile;
	int							outfile;
	char						*infile_name;
	char						*outfile_name;
	struct s_list2_simple_cmd	*next;
}					t_list2_simple_cmd;

typedef struct s_list2
{
	 t_list2_simple_cmd *premier;
	 char **env;
}					t_list2;

typedef struct s_exec_loop
{
	int tmpin;
    int tmpout;
    int fdin;
    int fdout;
	int fdpipe[2];
	int ret;
	char *redirect_path;
	// char **path_tab;
}					t_exec_loop;

typedef struct s_mem
{
	char **my_env;
	t_exec_loop *exec_loop;
}					t_mem;

typedef struct s_outlst
{
	char			*filename;
	int				action;
	struct s_outlst	*next;
}	t_outlst;

typedef struct s_cmdlst
{
	char			*command;
	char			**args;
	char			**infiles;
	t_outlst		*outfiles;
	char			**heredocs;
	int				todo_next;
	struct s_cmdlst	*next;
}	t_cmdlst;

char **str_to_wordtab(char * str);

// init

t_mem	*initialize_mem(void);

// list

t_list2_simple_cmd	*ft_lstlast2(t_list2_simple_cmd *lst);
t_list2              *initialisation();
t_list2_simple_cmd	*ft_lstnew2(char **content);
void                ft_lstadd_back2(t_list2 *list, t_list2_simple_cmd *new_elm);
void				aff_list(t_list2 *list);
int					list_len(t_list2 *list);
void    			free_list(t_list2 *list);

//	path

char    *find_right_path(char **path_tab, char *cmd, char *right_path);
char    *find_path_redirect_file(char *pwd, char *actuel, char *redirect_path);

//

void     do_list_simple_cmd(char **tab_pipe_split, t_list2 *list);
void    check_redirection(t_list2 *list);
void    check_var(char **cmd, char **my_env);

// exec

void 	execute(t_list2 *list, char **path_tab, char **env, t_mem *mem);
void	execute2(t_list2 *list, char **path_tab, char **env, t_mem *mem);
void 	execute3(t_cmdlst *lst, char **path_tab, char **env, t_mem *mem);

char    **ft_export(char **my_env, char *s);
void    ft_env(char **my_env);
char    **ft_unset(char **my_env, char *s);

// built-in

void ft_pwd(char **my_env);
// void ft_exit(t_list2 *list);
void	ft_exit();
void    ft_echo(char **s);
void 	ft_cd(char ** cmd, char **my_env);

// utils

int     tab_2d_len(char **tab);
int     first_word_is_exit(char *s);
void    free_tab_2d(char **tab);
char    **append_env(char **my_env, char *s);
char    **supp_elem_env(char **my_env, char *s);
int     is_in_env(char **my_env, char *s);
char 	*my_getenv(char **env, char *elem);
int		cmdlist_len(t_cmdlst *lst);
int    	outlst_len(t_outlst *lst);

// env_utils

char **append_tab_2d(char **tab, char *s);
char **supp_last_elem_tab2d(char **tab);
char *concat_path(char **tab, char *str);

/*
	PARSING
*/

# define NEXT_END		0
# define NEXT_PIPE		1
# define NEXT_AND		2
# define NEXT_OR		3

# define OUT_WRITE		0
# define OUT_APPEND		1

// parsing/check.c
int			check_quotes(char *command);
int			check_specials(t_list *args);

// parsing/cmdlst.c
t_cmdlst	*cmdlst_new(void);
t_cmdlst	*cmdlst_last(t_cmdlst *lst);
int			append_args(t_list **args, t_cmdlst *new, char *op, char ***array);
int			cmdlist_append_args(t_list **args, t_cmdlst *new);
int			create_command_lst(t_cmdlst **command_list, t_list *args);
// parsing/free.c
int			cmdlst_clear(t_cmdlst **lst);
int			outlst_clear(t_outlst **lst);
int			free_array_n(char **array, int n);
int			lst_clear(t_list **lst);
int			strarr_free(char **array);
// parsing/lst.c
int			lst_append(t_list **lst, char *str);
int			strarr_len(char **array);
int			strarr_append(char ***array, char *str);
// parsing/outfiles.c
int			outlst_append(t_outlst **lst, char *filename, char *spe);
int			append_out_args(t_list **args,
				t_cmdlst *new, char *op, t_outlst **out);
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
int			is_sep(char *str);

#endif
