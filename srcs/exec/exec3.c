#include "../../include/minishell.h"

void    init_exec(t_mem *mem, t_cmdlst *lst)
{
    if (cmdlist_len(lst) == 1 && (strcmp(lst->command, "exit") == 0))
        ft_exit();
    mem->exec_loop->tmpin = dup(0);
    mem->exec_loop->tmpout = dup(1);
    if (lst->infiles)
      mem->exec_loop->fdin = open(lst->infiles[0], O_RDONLY);
    else
      mem->exec_loop->fdin = dup(mem->exec_loop->tmpin);
}

void    reset_exec(t_mem *mem)
{
    dup2(mem->exec_loop->tmpin,0);
    dup2(mem->exec_loop->tmpout,1);
    close(mem->exec_loop->tmpin);
    close(mem->exec_loop->tmpout);
    if (mem->exec_loop->redirect_path)
        free(mem->exec_loop->redirect_path);
    mem->exec_loop->redirect_path = NULL;
}

void    set_up_output(t_mem *mem, t_cmdlst *lst, int i)
{
    if (i > 0)
        lst->outfiles = lst->outfiles->next;
    if (lst->next == NULL)
    {
        if (lst->outfiles)
        {
            if(lst->outfiles->action == 0)
            {
                mem->exec_loop->redirect_path = find_path_redirect_file(getenv("PWD"), lst->outfiles->filename, mem->exec_loop->redirect_path);
                mem->exec_loop->fdout = open( mem->exec_loop->redirect_path, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXO | S_IRWXU | S_IRWXG);
            }
            else if (lst->outfiles->action == 1)
            {
                mem->exec_loop->redirect_path = find_path_redirect_file(getenv("PWD"), lst->outfiles->filename, mem->exec_loop->redirect_path);
                mem->exec_loop->fdout = open( mem->exec_loop->redirect_path, O_APPEND | O_CREAT | O_WRONLY, S_IRWXO | S_IRWXU | S_IRWXG);
            }
        }
        else
            mem->exec_loop->fdout = dup(mem->exec_loop->tmpout);
    }
    else
    {
        pipe(mem->exec_loop->fdpipe);
        mem->exec_loop->fdout = mem->exec_loop->fdpipe[1];
        mem->exec_loop->fdin = mem->exec_loop->fdpipe[0];
    }
}

void    exec_cmd(t_mem *mem, t_cmdlst *lst, char **path_tab, char **env)
{
    char *right_path;

    right_path = find_right_path(path_tab, lst->command, right_path);
    if (strcmp(lst->command, "pwd") == 0 || strcmp(lst->command, "export") == 0 || strcmp(lst->command, "env") == 0 || strcmp(lst->command, "unset") == 0 || strcmp(lst->command, "echo") == 0 || strcmp(lst->command, "cd") == 0)
    {
        if (strcmp(lst->command, "cd") == 0)
            _exit(1);
        if (strcmp(lst->command, "pwd") == 0)
            ft_pwd(mem->my_env);
        if (strcmp(lst->command, "env") == 0 && lst->next == NULL)
            ft_env(mem->my_env);
        if (strcmp(lst->command, "echo") == 0)
            ft_echo(lst->args);
        if (strcmp(lst->command, "export") == 0 && lst->next == NULL)
            _exit(1);
        if (strcmp(lst->command, "unset") == 0 && lst->next == NULL)
            _exit(1);
    }
    else
    {
        if (execve(right_path, lst->args, env) == -1)
        {
            write(1, strerror( errno ), ft_strlen(strerror( errno )));
            write(1, "\n", 1);
        }
    }
    _exit(1);
}

void execute3(t_cmdlst *lst, char **path_tab, char **env, t_mem *mem)
{
    int i;

    mem->exec_loop->redirect_path = NULL;
    init_exec(mem, lst);
    while (lst)
    {   
        if (outlst_len(lst->outfiles) > 0)
            i = 0;
        else
            i = -1;
        while (i < outlst_len(lst->outfiles))
        {
            dup2(mem->exec_loop->fdin, 0);
            close(mem->exec_loop->fdin);
            set_up_output(mem, lst, i);
            dup2(mem->exec_loop->fdout, 1);
            close(mem->exec_loop->fdout);
            mem->exec_loop->ret = fork();
            if(mem->exec_loop->ret == 0)
                exec_cmd(mem, lst, path_tab, env);
            if (strcmp(lst->command, "cd") == 0 && lst->next == NULL)
                ft_cd(lst->args, mem->my_env);
            if (strcmp(lst->command, "export") == 0 && lst->next == NULL)
                mem->my_env = ft_export(mem->my_env, lst->args[1]);
            if (strcmp(lst->command, "unset") == 0 && lst->next == NULL)
                mem->my_env = ft_unset(mem->my_env, lst->args[1]);
            i++;
        }
        lst = lst->next;
    }
    reset_exec(mem);
    waitpid(mem->exec_loop->ret, NULL, 0);
}