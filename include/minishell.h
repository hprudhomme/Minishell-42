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

# include "../libft/include/libft.h"

#include <sys/types.h>
#include <sys/wait.h>

# include <sys/stat.h>

#include <errno.h>

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
}					t_list2;

// typedef struct s_mem
// {
// 	 t_list2_simple_cmd *premier;
// }					t_mem;



char **str_to_wordtab(char * str);

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

// exec

void execute(t_list2 *list, char **path_tab);

// utils

int     tab_2d_len(char **tab);

#endif
