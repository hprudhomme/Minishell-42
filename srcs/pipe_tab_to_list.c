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
        if (cmd[tab_len][0] == '>' || cmd[tab_len][0] == '<')
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
            if (actuel->cmd[i][0] == '<' && ft_strlen(actuel->cmd[i]) == 1)
            {
                actuel->infile_name = ft_strdup(actuel->cmd[i + 1]);
                actuel->cmd = resize_tab(actuel->cmd);
                actuel->infile = 1;
                break ;
            }
            if (actuel->cmd[i][0] == '>' && actuel->cmd[i][1] == '>' && ft_strlen(actuel->cmd[i]) == 2)
            {
                actuel->outfile_name = ft_strdup(actuel->cmd[i + 1]);
                actuel->cmd = resize_tab(actuel->cmd);
                actuel->outfile = 2;
                break ;
            }
            if (actuel->cmd[i][0] == '>' && ft_strlen(actuel->cmd[i]) == 1)
            {
                actuel->outfile_name = ft_strdup(actuel->cmd[i + 1]);
                actuel->cmd = resize_tab(actuel->cmd);
                actuel->outfile = 1;
                break ;
            }
            i++;
        }
        actuel = actuel->next;
    }
}

// void    change_var2(char **my_env,char *temp, char *cmd, int start, int end)
// {
//     int i;
//     char *var_to_change;
//     int len;

//     i = 0;
//     var_to_change = my_getenv(my_env, temp);
//     while (i <= end))
//     {
//         if (cmd[i] == '"' || (i >= start && i <= end))
//             continue ;
//         else
//             len++;
//         i++;
//     }
//     while (cmd[i])
//     {
//         if ()
//     }
    
// }

int     check_simple_guill(char *cmd, int start, int end)
{
    int i;
    int count;

    count = 0;
    i = 0;
    while (i < start)
    {
        if (cmd[i] == '\'')
            count++;
        i++;
    }
    if (count > 1)
        return 0;
    while (cmd[i])
    {
        if (cmd[i] == '\'')
        {
            count++;
            break ;
        }
        i++;
    }
    if (count == 2)
        return 1;
    return 0;
}

void    change_var(char *cmd, int start, char **my_env)
{
    int len;
    char *temp;
    int i;
    int save_start;
    int end;

    save_start = start;
    i = start + 1;
    while (cmd[i] && cmd[i] != '"' && cmd[i] != '$' && cmd[start] != '\'')
    {
        i++;
        len++;
    }
    if (check_simple_guill(cmd, start, i))
    {
        printf("is_guill\n");
        return ;
    }
    temp = malloc(sizeof(char) * (len + 1));
    i = 0;
    start++;
    while (cmd[start] && cmd[start] != '"' && cmd[start] != '$' && cmd[start] != '\'')
        temp[i++] = cmd[start++];
    temp[i] = '\0';
    if (!is_in_env(my_env, temp))
    {
        printf("%s is not in env\n", temp);
        free(temp);
        temp = NULL;
    }
    if (cmd[start])
        end = start;
    else
        end = start - 1;
    printf("s = %s\n", temp);
    //change_var2(my_env, temp, cmd, save_start, end);
}

void    check_var(char **cmd, char **my_env)
{
    int i;
    int j;
    int is_doll;

    i = 0;
    j = 0;
    while (cmd[i])
    {
        j = 0;
        while (cmd[i][j])
        {
            if (cmd[i][j] == '$')
                change_var(cmd[i], j, my_env);
            j++;
        }
        i++;
    }
}