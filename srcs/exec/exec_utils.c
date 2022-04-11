#include "../../include/minishell.h"

void    set_up_output(t_mem *mem, t_cmdlst *lst, int i)
{
    if (i > 0)
        lst->outfiles = lst->outfiles->next;
    if (lst->todo_next != 1)
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

void     init_outlst_loop(t_mem *mem, t_cmdlst *lst, int i)
{
    dup2(mem->exec_loop->fdin, 0);
    close(mem->exec_loop->fdin);
    set_up_output(mem, lst, i);
    dup2(mem->exec_loop->fdout, 1);
    close(mem->exec_loop->fdout);
}

int     save_last_exit_statue(t_mem *mem, t_cmdlst *lst)
{
    mem->last_cmd_exit_statue = mem->exit_statue;
    if (mem->exit_statue == 0 && lst->todo_next == 3)
    {
        mem->last_cmd_exit_statue = mem->exit_statue;
        return (1);
    }
    if (mem->exit_statue != 0 && lst->todo_next == 2)
    {
        mem->last_cmd_exit_statue = mem->exit_statue;
        return (1);
    }
    if (lst->todo_next == 2 || lst->todo_next == 3)
    {
        mem->last_cmd_exit_statue = mem->exit_statue;
        reset_exec(mem);
        init_exec(mem, lst);
    }
    return (0);
}