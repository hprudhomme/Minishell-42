// #include "../../include/minishell.h"

// void    init_exec(t_mem *mem, t_list2_simple_cmd *actuel, t_list2 *list)
// {
//     if (list_len(list) == 1 && (strcmp(actuel->cmd[0], "exit") == 0))
//         ft_exit(list);
//     mem->exec_loop->tmpin = dup(0);
//     mem->exec_loop->tmpout = dup(1);
//     if (actuel->infile)
//       mem->exec_loop->fdin = open(actuel->infile_name, O_RDONLY);
//     else
//       mem->exec_loop->fdin = dup(mem->exec_loop->tmpin);
// }

// void    reset_exec(t_mem *mem, t_list2_simple_cmd *actuel)
// {
//     dup2(mem->exec_loop->tmpin,0);
//     dup2(mem->exec_loop->tmpout,1);
//     close(mem->exec_loop->tmpin);
//     close(mem->exec_loop->tmpout);
//     if (mem->exec_loop->redirect_path)
//         free(mem->exec_loop->redirect_path);
//     mem->exec_loop->redirect_path = NULL;
// }

// void    set_up_output(t_mem *mem, t_list2_simple_cmd *actuel)
// {
//     if (actuel->next == NULL)
//     {
//         if(actuel->outfile == 1)
//         {
//             mem->exec_loop->redirect_path = find_path_redirect_file(getenv("PWD"), actuel->outfile_name, mem->exec_loop->redirect_path);
//             mem->exec_loop->fdout = open( mem->exec_loop->redirect_path, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXO | S_IRWXU | S_IRWXG);
//         }
//         else if (actuel->outfile == 2)
//         {
//             mem->exec_loop->redirect_path = find_path_redirect_file(getenv("PWD"), actuel->outfile_name, mem->exec_loop->redirect_path);
//             mem->exec_loop->fdout = open( mem->exec_loop->redirect_path, O_APPEND | O_CREAT | O_WRONLY, S_IRWXO | S_IRWXU | S_IRWXG);
//         }
//         else
//         mem->exec_loop->fdout = dup(mem->exec_loop->tmpout);
//     }
//     else
//     {
//         pipe(mem->exec_loop->fdpipe);
//         mem->exec_loop->fdout = mem->exec_loop->fdpipe[1];
//         mem->exec_loop->fdin = mem->exec_loop->fdpipe[0];
//     }
// }

// void    exec_cmd(t_mem *mem, t_list2_simple_cmd *actuel, char **path_tab, char **env)
// {
//     char *right_path;

//     right_path = find_right_path(path_tab, actuel->cmd[0], right_path);
//     if (strcmp(actuel->cmd[0], "pwd") == 0 || strcmp(actuel->cmd[0], "export") == 0 || strcmp(actuel->cmd[0], "env") == 0 || strcmp(actuel->cmd[0], "unset") == 0 || strcmp(actuel->cmd[0], "echo") == 0 || strcmp(actuel->cmd[0], "cd") == 0)
//     {
//         if (strcmp(actuel->cmd[0], "cd") == 0)
//             _exit(1);
//         if (strcmp(actuel->cmd[0], "pwd") == 0)
//             ft_pwd(mem->my_env);
//         if (strcmp(actuel->cmd[0], "env") == 0 && actuel->next == NULL)
//             ft_env(mem->my_env);
//         if (strcmp(actuel->cmd[0], "echo") == 0)
//             ft_echo(actuel->cmd);
//         if (strcmp(actuel->cmd[0], "export") == 0 && actuel->next == NULL)
//             _exit(1);
//         if (strcmp(actuel->cmd[0], "unset") == 0 && actuel->next == NULL)
//             _exit(1);
//     }
//     else
//     {
//         if (execve(right_path, actuel->cmd, env) == -1)
//         {
//             write(1, strerror( errno ), ft_strlen(strerror( errno )));
//             write(1, "\n", 1);
//         }
//     }
//     _exit(1);
// }

// void execute2(t_list2 *list, char **path_tab, char **env, t_mem *mem)
// {
//     t_list2_simple_cmd *actuel;

//     actuel = list->premier;
//     mem->exec_loop->redirect_path = NULL;
//     init_exec(mem, actuel, list);
//     while (actuel != NULL)
//     {
//         dup2(mem->exec_loop->fdin, 0);
//         close(mem->exec_loop->fdin);
//         set_up_output(mem, actuel);
//         dup2(mem->exec_loop->fdout, 1);
//         close(mem->exec_loop->fdout);
//         mem->exec_loop->ret = fork();
//         if(mem->exec_loop->ret == 0)
//             exec_cmd(mem, actuel, path_tab, env);
//         if (strcmp(actuel->cmd[0], "cd") == 0 && actuel->next == NULL)
//             ft_cd(actuel->cmd, mem->my_env);
//         if (strcmp(actuel->cmd[0], "export") == 0 && actuel->next == NULL)
//             mem->my_env = ft_export(mem->my_env, actuel->cmd[1]);
//         if (strcmp(actuel->cmd[0], "unset") == 0 && actuel->next == NULL)
//             mem->my_env = ft_unset(mem->my_env, actuel->cmd[1]);
//         actuel = actuel->next;
//     }
//     reset_exec(mem, actuel);
//     waitpid(mem->exec_loop->ret, NULL, 0);
// }
