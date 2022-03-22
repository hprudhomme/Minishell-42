# include "minishell.h"

t_list_simple_cmd	*ft_lstlast(t_list_simple_cmd *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_list *initialisation()
{
    t_list *liste = (t_list *)malloc(sizeof(t_list));
    t_list_simple_cmd *simple_cmd = (t_list_simple_cmd *)malloc(sizeof(t_list_simple_cmd));

    if (liste == NULL || simple_cmd == NULL)
        exit(EXIT_FAILURE);

    simple_cmd->nb = 1;
    simple_cmd->cmd = NULL;
    simple_cmd->infile = 0;
    simple_cmd->outfile = 0;
    simple_cmd->infile_name = NULL;
    simple_cmd->outfile_name = NULL;
    simple_cmd->next = NULL;
    liste->premier = simple_cmd;

    return liste;
}

t_list_simple_cmd	*ft_lstnew(char **content)
{
	t_list_simple_cmd	*elmt;

	elmt = ((t_list_simple_cmd *)malloc(sizeof(*elmt)));
	if (!elmt)
		return (NULL);
	elmt->cmd = content;
    elmt->infile = 0;
    elmt->outfile = 0;
    elmt->infile_name = NULL;
    elmt->outfile_name = NULL;
	elmt->next = NULL;
	return (elmt);
}

void	ft_lstadd_back(t_list *list, t_list_simple_cmd *new_elm)
{
	t_list_simple_cmd	*last_elem;

	last_elem = ft_lstlast(list->premier);
	last_elem->next = new_elm;
}

void    aff_list(t_list *list)
{
    if (list == NULL)
    {
        exit(EXIT_FAILURE);
    }

    t_list_simple_cmd *actuel = list->premier;

    while (actuel != NULL)
    {
        printf("-----------start----------\n");
        int i = 0;
        while (actuel->cmd[i])
        {
            printf("%s\n", actuel->cmd[i]);
            i++;
        }
        printf("outfile : %d\n", actuel->outfile);
        printf("outfile_name : %s\n", actuel->outfile_name);
        actuel = actuel->next;
        printf("-----------end----------\n");
    }
    printf("TERMINER\n");
}

int    list_len(t_list *list)
{
    int i;
    t_list_simple_cmd *actuel;

    if (list == NULL)
        exit(EXIT_FAILURE);
    i = 0;
    actuel = list->premier;
    while (actuel != NULL)
    {
        i++;        
        actuel = actuel->next;
    }
    return (i);
}

void    free_list(t_list *list)
{
    int                 i;
    t_list_simple_cmd   *actuel;

    i = 0;
    if (list == NULL)
        exit(EXIT_FAILURE);
    while (i <= list_len(list))
    {
        actuel = list->premier;
        if (list->premier != NULL)
        {   
            int i = 0;
            while (list->premier->cmd[i])
            {
                free(list->premier->cmd[i]);
                i++;
            }
            if (list->premier->cmd)
                free(list->premier->cmd);
            list->premier = actuel->next;
            if (actuel)
                free(actuel);
        }
        i++;
    }
}