#include "../../include/minishell.h"

int     is_builtin(char *cmd)
{
    if (strcmp(cmd, "cd") == 0)
        return (2);
    if (strcmp(cmd, "exit") == 0)
        return (2);
    if (strcmp(cmd, "pwd") == 0)
        return (1);
    if (strcmp(cmd, "env") == 0)
        return (1);
    if (strcmp(cmd, "echo") == 0)
        return (1);
    if (strcmp(cmd, "export") == 0)
        return (2);
    if (strcmp(cmd, "unset") == 0)
        return (2);
    return (0);
}

void    init_exec(t_mem *mem, t_cmdlst *lst)
{
    mem->exec_loop->tmpin = dup(0);
    mem->exec_loop->tmpout = dup(1);
    if (lst->infiles)
        mem->exec_loop->fdin = open(lst->infiles[0], O_RDONLY);
    else
        mem->exec_loop->fdin = dup(mem->exec_loop->tmpin);
    mem->exit_statue = 0;
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
    mem->exec_loop->right_path = NULL;
    mem->exit_statue = 0;
}