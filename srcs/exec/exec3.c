#include "../../include/minishell.h"

void    exec_cmd(t_mem *mem, t_cmdlst *lst, char **env)
{
    char *right_path;

    right_path = find_right_path(mem->path_tab, lst->command, right_path);
    if (strcmp(lst->command, "exit") == 0 || strcmp(lst->command, "pwd") == 0 || strcmp(lst->command, "export") == 0 || strcmp(lst->command, "env") == 0 || strcmp(lst->command, "unset") == 0 || strcmp(lst->command, "echo") == 0 || strcmp(lst->command, "cd") == 0)
    {
        if (strcmp(lst->command, "cd") == 0 || strcmp(lst->command, "exit") == 0 || strcmp(lst->command, "export") == 0 || strcmp(lst->command, "unset") == 0)
            exit(0);
        if (strcmp(lst->command, "pwd") == 0)
            ft_pwd(mem->my_env, mem);
        if (strcmp(lst->command, "env") == 0)
            ft_env(mem->my_env, mem);
        if (strcmp(lst->command, "echo") == 0)
            ft_echo(lst->args, mem);
    }
    else
    {
        if (execve(right_path, lst->args, mem->my_env) == -1)
        {
            write(1, strerror( errno ), ft_strlen(strerror( errno )));
            write(1, "\n", 1);
            exit(1);
        }
    }
    exit(0);
}

int     do_builtin(t_cmdlst *lst, t_mem *mem)
{
    if (strcmp(lst->command, "cd") == 0 && lst->todo_next != 1)
        ft_cd(lst->args, mem);
    if (strcmp(lst->command, "export") == 0 && lst->todo_next != 1)
        if (!ft_exports(mem, lst->args))
			return (0);
    if (strcmp(lst->command, "unset") == 0 && lst->todo_next != 1)
        mem->my_env = ft_unsets(mem, lst->args);
    return 1;
}

void    exec_next(t_cmdlst *lst, char **env, t_mem *mem, int i)
{
    init_outlst_loop(mem, lst, i);
    mem->exec_loop->ret = fork();
    if(mem->exec_loop->ret == 0)
        exec_cmd(mem, lst, env);
    waitpid(mem->exec_loop->ret, &(mem->exit_statue), 0);
    if ((strcmp(lst->command, "cd") == 0 && lst->todo_next != 1) || (strcmp(lst->command, "export") == 0 && lst->todo_next != 1) || (strcmp(lst->command, "unset") == 0 && lst->todo_next != 1))
        do_builtin(lst, mem);
    if (lst->heredocs)
        delete_tpmfile(mem);
}

void execute3(t_cmdlst *lst, char **env, t_mem *mem)
{
    int i;

    mem->exec_loop->redirect_path = NULL;
    init_exec(mem, lst);
    while (lst)
    {
        setup_infiles(lst, mem);
        if ((strcmp(lst->command, "exit") == 0) && ((lst->todo_next == 0 && cmdlist_len(lst) == 1) || lst->todo_next == 2 || lst->todo_next == 3))
            ft_exit(mem, lst);
        replace_quotes(&(lst->args), mem->my_env, mem->last_cmd_exit_statue);
        if (outlst_len(lst->outfiles) > 0)
            i = 0;
        else
            i = -1;
        while (i < outlst_len(lst->outfiles))
        {
            exec_next(lst, env, mem, i);
            i++;
        }
        if (save_last_exit_statue(mem, lst))
            lst = lst->next;
        lst = lst->next;
    }
    reset_exec(mem);
}
