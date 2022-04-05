#include "../../include/minishell.h"

void execute(t_list2 *list, char **path_tab, char **env, t_mem *mem)
{
    char *redirect_path;
    char *pwd = getenv("PWD");
    // printf("pwd = %s\n", pwd);
    char *right_path;

    t_list2_simple_cmd *actuel = list->premier;
    int i;
    int numsimplecommands;
    //save in/out
    int tmpin=dup(0);
    int tmpout=dup(1);

    //set the initial input
    int fdin;
    if (actuel->infile)
      fdin = open(actuel->infile_name, O_RDONLY);
    else {
      // Use default input
      fdin=dup(tmpin);
    }

    int ret;
    int fdout;

    check_var(actuel->cmd, mem->my_env);

    redirect_path = NULL;
    i = 0;
    numsimplecommands = list_len(list);
    if (numsimplecommands == 1 && (strcmp(actuel->cmd[0], "exit") == 0))
        ft_exit(list);
    while (actuel != NULL)
    {
        //redirect input
        dup2(fdin, 0);
        close(fdin);
        //setup output
        if (actuel->next == NULL)
        {
            // Last simple command
            if(actuel->outfile == 1)
            {
                printf("buzz\n");
                redirect_path = find_path_redirect_file(getenv("PWD"), actuel->outfile_name, redirect_path);
                fdout = open(redirect_path, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXO | S_IRWXU | S_IRWXG);
            }
            else if (actuel->outfile == 2)
            {
                printf("buzz2\n");
                redirect_path = find_path_redirect_file(getenv("PWD"), actuel->outfile_name, redirect_path);
                fdout = open(redirect_path, O_APPEND | O_CREAT | O_WRONLY, S_IRWXO | S_IRWXU | S_IRWXG);
                // write(fdout, "end", ft_strlen("end"));
            }
            else
            {
            // Use default output
            fdout = dup(tmpout);
            }
        }

        else
        {
            // Not last
            //simple command
            //create pipe
            int fdpipe[2];
            pipe(fdpipe);
            fdout = fdpipe[1];
            fdin = fdpipe[0];
        }

        // Redirect output
        dup2(fdout,1);
        close(fdout);

        // Create child process
        ret = fork();
        if(ret == 0)
        {
            right_path = find_right_path(path_tab, actuel->cmd[0], right_path);
            // printf("path = %s\n", right_path);
            if (strcmp(actuel->cmd[0], "pwd") == 0 || strcmp(actuel->cmd[0], "export") == 0 || strcmp(actuel->cmd[0], "env") == 0 || strcmp(actuel->cmd[0], "unset") == 0 || strcmp(actuel->cmd[0], "echo") == 0 || strcmp(actuel->cmd[0], "cd") == 0)
            {
                if (strcmp(actuel->cmd[0], "cd") == 0)
                    _exit(1);
                if (strcmp(actuel->cmd[0], "pwd") == 0)
                    ft_pwd(mem->my_env);
                if (strcmp(actuel->cmd[0], "env") == 0 && actuel->next == NULL)
                    ft_env(mem->my_env);
                if (strcmp(actuel->cmd[0], "echo") == 0)
                    ft_echo(actuel->cmd);
                if (strcmp(actuel->cmd[0], "export") == 0 && actuel->next == NULL)
                    _exit(1);
                if (strcmp(actuel->cmd[0], "unset") == 0 && actuel->next == NULL)
                    _exit(1);
            }
            else
            {
                if (execve(right_path, actuel->cmd, env) == -1)
                {
                    write(1, strerror( errno ), ft_strlen(strerror( errno )));
                    write(1, "\n", 1);
                }
            }
            _exit(1);
        }
        if (strcmp(actuel->cmd[0], "cd") == 0 && actuel->next == NULL)
            ft_cd(actuel->cmd, mem->my_env);
        if (strcmp(actuel->cmd[0], "export") == 0 && actuel->next == NULL)
            mem->my_env = ft_export(mem->my_env, actuel->cmd[1]);
        if (strcmp(actuel->cmd[0], "unset") == 0 && actuel->next == NULL)
            mem->my_env = ft_unset(mem->my_env, actuel->cmd[1]);
        i++;
        actuel = actuel->next;
    }

     //restore in/out defaults
    // if (strcmp(actuel->cmd[0], "export") == 0)
    // {
    //     printf("buzz3\n");
    //     my_env = ft_export(my_env, actuel->cmd[1]);
    // }
    dup2(tmpin,0);
    dup2(tmpout,1);
    close(tmpin);
    close(tmpout);
    redirect_path = NULL;

    // if (!background)
    // {
        // Wait for last command
    waitpid(ret, NULL, 0);
    // }
}
