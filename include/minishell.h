/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:57:56 by ocartier          #+#    #+#             */
/*   Updated: 2022/04/18 21:35:42 by ocartier         ###   ########.fr       */
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
# include <sys/signal.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/include/libft.h"

/*
	EXEC
*/
typedef struct s_list2_simple_cmd
{
	int							nb;
	char						**cmd;
	int							infile;
	int							outfile;
	char						*infile_name;
	char						*outfile_name;
	struct s_list2_simple_cmd	*next;
}	t_list2_simple_cmd;

typedef struct s_list2
{
	t_list2_simple_cmd	*premier;
	char				**env;
}	t_list2;

typedef struct s_exec_loop
{
	int		tmpin;
	int		tmpout;
	int		fdin;
	int		fdout;
	int		fdpipe[2];
	int		ret;
	char	*redirect_file_path;
	char	*right_path;
}	t_exec_loop;

typedef struct s_mem
{
	char		**my_env;
	char		**path_tab;
	char		*exec_path;
	char		*path_env;
	int			exit_statue;
	int			last_cmd_exit_statue;
	int			fd_heredocs[2];
	char		*tmpfile;
	t_exec_loop	*exec_loop;
}	t_mem;

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

// init

t_mem		*initialize_mem(void);

// free

void		free_mem(t_mem *mem, int exiting);
void		free_path(t_mem *mem);

//	path

char		*find_exec_path(char **path_tab, char *cmd, char *right_path);
char		*find_path_redirect_file(char *pwd, char *actuel,
				char *redirect_path);

// exec

void		execute(t_cmdlst *lst, t_mem *mem);

//	exec_utils

void		init_outlst_loop(t_mem *mem, t_cmdlst *lst, int i);
int			save_last_exit_statue(t_mem *mem, t_cmdlst *lst);
void		init_exec(t_mem *mem, t_cmdlst *lst);
void		reset_exec(t_mem *mem);
int			is_builtin(char *cmd);
void		write_exit_statue(t_mem *mem, int i);
void		init_exec_cmd(t_mem *mem, t_cmdlst *lst);
int			is_exiting(t_cmdlst *lst);
int			exec_builtin(t_mem *mem, t_cmdlst *lst);

// exec_infiles

void		handle_heredocs(t_mem *mem, t_cmdlst *lst);
void		setup_infiles(t_cmdlst *lst, t_mem *mem);
void		delete_tpmfile(t_mem *mem);

// env fct in env.c

char		**copy_env(char **env);
char		*my_getenv(char **env, char *elem);
int			my_env_index_elem(char **my_env, char *elem);

// built-in

int			ft_export(t_mem *mem, char *s);
int			ft_exports(t_mem *mem, char **args);
int			ft_env(t_mem *mem);
int			ft_unsets(t_mem *mem, char **args);
char		**ft_unset(t_mem *mem, char *var);

int			ft_pwd(t_mem *mem);
void		ft_exit(t_mem *mem, t_cmdlst *lst);
int			ft_echo(char **s, t_mem *mem);
void		ft_cd(char **cmd, t_mem *mem);

// cd2.c

char		**change_oldpwd(char *pwd, char **my_env);
char		**change_pwd(char **temp2, char **my_env);
char		**change_pwd_home(char **my_env);

// utils

int			tab_2d_len(char **tab);
void		free_tab_2d(char **tab);
char		**append_env(char **my_env, char *s);
char		**supp_elem_env(char **my_env, char *s);
int			is_in_env(char **my_env, char *s);
char		*my_getenv(char **env, char *elem);
int			cmdlist_len(t_cmdlst *lst);
int			outlst_len(t_outlst *lst);

// env_utils

char		**append_tab_2d(char **tab, char *s);
char		**supp_last_elem_tab2d(char **tab);
char		*concat_path(char **tab, char *str);

/*
	PARSING
*/

# define NEXT_END		0
# define NEXT_PIPE		1
# define NEXT_AND		2
# define NEXT_OR		3
# define NEXT_CONTINUE	4

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
// parsing/env.c
char		*get_env(char *env_name, char **env, int last_exit);
int			get_envvar_size(char *str);
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
int			append_out_args(t_list **args, char *op, t_outlst **out);
// parsing/parsing.c
int			get_arg_end(char *str, int quote_index);
int			get_quotes_end(char *str, int e_end);
int			get_end_index(char *str, int e_end);
int			split_args(t_list **args, char *cmd);
t_cmdlst	*parsing(char *command);
// parsing/quotes.c
int			replace_quotes(char ***args, char **env, int last_exit);
int			set_in_quotes(char c, int *in_quotes);
// parsing/utils.c
int			index_of(char *str, char *search, int n);
int			get_arg_type(char *str);
int			is_sep(char *str);

// ft_utils.c
int			ft_strcmp(char *s1, char *s2);
int			strcmp_len(char *s1, char *s2);
int			ft_strcat(char *dst, char *src);
char		*ft_strldup(const char *s1, size_t size);
// utils.c
void		*nil(int i);
int			free_str(char *str);
int			contains_only(char *str, char c);
int			replace_var(char *var_val, char *n_arg, int *n_cur);
#endif
