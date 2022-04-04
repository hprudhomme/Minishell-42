#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# include<readline/readline.h>
# include<readline/history.h>

# include <math.h>
# include <string.h>

# include "../libft/libft.h"

#include <sys/types.h>
#include <sys/wait.h>

# include <sys/stat.h>

#include <errno.h>

#include <signal.h>

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



char **str_to_wordtab(char * str);

// init

t_mem	*initialize_mem(void);

// list

t_list2_simple_cmd	*ft_lstlast(t_list2_simple_cmd *lst);
t_list2              *initialisation();
t_list2_simple_cmd	*ft_lstnew(char **content);
void                ft_lstadd_back(t_list2 *list, t_list2_simple_cmd *new_elm);
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

char    **ft_export(char **my_env, char *s);
void    ft_env(char **my_env);
char    **ft_unset(char **my_env, char *s);

// built-in

void ft_pwd(char **my_env);
void ft_exit(t_list2 *list);
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

// env_utils

char **append_tab_2d(char **tab, char *s);
char **supp_last_elem_tab2d(char **tab);
char *concat_path(char **tab, char *str);


#endif
