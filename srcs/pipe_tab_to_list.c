# include "../include/minishell.h"

void     do_list_simple_cmd(char **tab_pipe_split, t_list2 *list)
{

    int i;

    i = 0;
    while (tab_pipe_split[i])
    {
        if (i == 0)
            list->premier->cmd = ft_split(tab_pipe_split[i], ' ');
        else
            ft_lstadd_back(list, ft_lstnew(ft_split(tab_pipe_split[i], ' ')));
        i++;
    }
}

char    **resize_tab(char **cmd)
{
    int i;
    int tab_len;
    char **dest;

    i = 0;
    tab_len = 0;
    while (cmd[tab_len])
    {
        if (cmd[tab_len][0] == '>')
            break ;
        tab_len++;
    }
    dest = (char **)malloc(sizeof(char) * (tab_len + 1));
    while (i < tab_len)
    {
        dest[i] = ft_strdup(cmd[i]);
        free(cmd[i]);
        i++;
    }
    dest[i] = NULL;
    while (cmd[i])
        free(cmd[i++]);
    free(cmd);
    i = 0;
    return (dest);
}

void    check_redirection(t_list2 *list)
{
    if (list == NULL)
        exit(EXIT_FAILURE);

    t_list2_simple_cmd *actuel = list->premier;

    while (actuel != NULL)
    {
        int i;
        int j;

        i = 0;
        while (actuel->cmd[i])
        {
            if (actuel->cmd[i][0] == '>' && ft_strlen(actuel->cmd[i]) == 1)
            {
                actuel->outfile_name = ft_strdup(actuel->cmd[i + 1]);
                actuel->cmd = resize_tab(actuel->cmd);
                actuel->outfile = 1;
                break ;
            }
            if (actuel->cmd[i][0] == '>' && actuel->cmd[i][1] == '>' && ft_strlen(actuel->cmd[i]) == 2)
            {
                actuel->outfile_name = ft_strdup(actuel->cmd[i + 1]);
                actuel->cmd = resize_tab(actuel->cmd);
                actuel->outfile = 2;
                break ;
            }
            i++;
        }
        actuel = actuel->next;
    }
}
