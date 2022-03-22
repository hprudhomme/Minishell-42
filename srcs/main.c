# include "../include/minishell.h"

char *my_getenv(char **env, char *elem/*"PATH"*/)
{
    char    *str;
    int     i;
    int     x;
    int path_len;
  /* je parcours l’env, je trouve la ligne qui commence par PATH*/
  /* j’envoie l’adresse de ce qui se trouve apres le ’=’ */

    path_len = ft_strlen(elem);
    int index = 0;
    while (env[index])
    {
        // if (env[index][0] == 'P' && env[index][1] == 'A' && env[index][2] == 'T' && env[index][3] == 'H')
        //     break ;
        if (ft_strncmp(elem, env[index], path_len) == 0)
            break ;
        index++;
    }
    str = malloc(sizeof(char) * (ft_strlen(env[index]) - path_len));

    i = path_len + 1;
    x = 0;
    while (env[index][i])
    {
        str[x] = env[index][i];
        i++;
        x++;
    }
    return (str);
}

int takeInput(char* str)
{
	char* buf;

	buf = readline(">> ");
	if (strlen(buf) != 0) {
		add_history(buf);
		//str = ft_strdup(buf);
        // str = malloc(sizeof(char) * ft_strlen(buf));
		strcpy(str, buf);
		return 0;
	} else {
		return 1;
	}
}

void    exec_pipe(t_list2 *list, char **path_tab)
{
    char *redirect_path;
    char *pwd = getenv("PWD");
    char *right_path;
    if (list == NULL)
    {
        exit(EXIT_FAILURE);
    }

    t_list2_simple_cmd *actuel = list->premier;
    	// 0 is read end, 1 is write end
	int pipefd[2];
	pid_t p1, p2;

	if (pipe(pipefd) < 0) {
		printf("\nPipe could not be initialized");
		return;
	}
	p1 = fork();
	if (p1 < 0) {
		printf("\nCould not fork");
		return;
	}
	// printf("p1 = %d\n", p1);
	if (p1 == 0) {
		// Child 1 executing..
		// It only needs to write at the write end
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO); //  stdout = pipefd[1] // change la sortie standard (console) pr la mettre dans fd[1]
		close(pipefd[1]);

        right_path = find_right_path(path_tab, actuel->cmd[0], right_path);

		if (execve(right_path,actuel->cmd, NULL) < 0) {
			printf("\nCould not execute command 1..");
			exit(0);
		}
	} else {
		// Parent executing
        actuel = actuel->next;
		p2 = fork();
		if (p2 < 0) {
			printf("\nCould not fork");
			return;
		}

		// Child 2 executing..
		// It only needs to read at the read end
		if (p2 == 0) {
            // printf("actuel->cmd[2] = %s\n", actuel->cmd[2]);
            if (actuel->cmd[2][0] == '>')
            {
                printf("buzz\n");
                redirect_path = find_path_redirect_file(pwd, actuel->cmd[3], redirect_path);
                printf("redirect path = %s\n", redirect_path);
                // if (redirect_path != NULL)
                // {
                    close(pipefd[1]);
			        dup2(pipefd[0], open(redirect_path, O_CREAT | O_WRONLY | O_TRUNC)); // stdin = pipefd[0] qui est la sortie deniere de pipefd[1]
			        close(pipefd[0]);
                // }
                // open(redirect_path, O_RDWR, O_CREAT);
            }
            else
            {
                close(pipefd[1]);
			    dup2(pipefd[0], STDIN_FILENO); // stdin = pipefd[0] qui est la sortie deniere de pipefd[1]
			    close(pipefd[0]);
            }
            right_path = find_right_path(path_tab, actuel->cmd[0], right_path);
			if (execve(right_path,actuel->cmd, NULL) < 0) {
				printf("\nCould not execute command 2..");
				exit(0);
			}
		} else {
			// parent executing, waiting for two children
			wait(NULL);
			wait(NULL);
		}
	}
}

// int main(int argc, char **argv, char **env)
// {
//     char *str;
//     char *env_path;
//     char ** array = NULL;
//     int pid;
//     int len;

//     char **tab_pipe_split;
//     char **path_tab;
//     char *right_path;

//     t_list2 *list;

//     list = initialisation();
//     // printf("%d\n", list->premier->nb);
//     // list->premier->cmd = str_to_wordtab("ls -la");

//     env_path = getenv("PATH");
//     path_tab = ft_split(env_path, ':');

//     while (42)
//     {
//         printf("mon_prompt>");
//         if (takeInput(str))
// 			continue;
//         tab_pipe_split = ft_split(str, '|');
//         len = tab_2d_len(tab_pipe_split);
//         if (len > 1)
//         {
//             printf("buzz\n");
//             do_list_simple_cmd(tab_pipe_split, list);
//             exec_pipe(list, path_tab);
//         }
//         else
//         {
//             array = str_to_wordtab(str);

//             right_path = find_right_path(path_tab, array[0], right_path);
//             pid = fork();
//             if (pid == 0)
//             {
//                 execve(right_path, array, NULL);
//             }
//             else
//                 wait(NULL);
//         }
//     }
// }

int main(int ac, char **av)
{
    char *str;
    char *env_path;
    char ** array = NULL;
    int pid;
    int len;

    char **tab_pipe_split;
    char **path_tab;
    char *right_path;

    t_list2 *list;

    env_path = getenv("PATH");
    path_tab = ft_split(env_path, ':');
    while (42)
    {
        list = initialisation();
        printf("mon_prompt>");
        if (takeInput(str))
			continue;
        tab_pipe_split = ft_split(str, '|');
        len = tab_2d_len(tab_pipe_split);

        do_list_simple_cmd(tab_pipe_split, list);
        check_redirection(list);
        execute(list, path_tab);

        free_list(list);
        if (list)
            free(list);
    }
}
