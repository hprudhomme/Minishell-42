#include "../../include/minishell.h"

int     tab_2d_len(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
        i++;
    return (i);
}

void    free_tab_2d(char **tab)
{
    // printf("-------- start free ------------\n");
    int i;

    i = 0;
    while (tab[i])
    {
        // printf("str = %s\n", tab[i]);
        if (tab[i])
            free(tab[i]);
        i++;
    }
    if (tab)
        free(tab);
    // printf("-------- end free ------------\n");
}

int     is_in_env(char **my_env, char *s)
{
    int i;
    char **temp;

    i = 0;
    while (my_env[i])
    {
        temp = ft_split(my_env[i], '=');
        if (strcmp(temp[0], s) == 0)
            break ;
        free_tab_2d(temp);
        i++;
    }
    if (temp)
        free_tab_2d(temp);
    if (i == tab_2d_len(my_env))
    {
        printf("var not find !!!\n");
        return 0;
    }
    return 1;
}

// char    **supp_elem_env(char **my_env, char *s)
// {
//     char **new;
//     char **temp;
//     int i;
//     int j;


//     if (!is_in_env(my_env, s))
//         return my_env;
//     i = 0;
//     j = 0;
//     new = (char **)malloc(sizeof(char *) * (tab_2d_len(my_env)));
//     if (!new)
//         return NULL;
//     i = 0;
//     while (my_env[i])
//     {
//         temp = ft_split(my_env[i], '=');
//         if (strcmp(temp[0], s) == 0)
//             i++;
//         else
//             new[j++] = ft_strdup(my_env[i++]);
//         free_tab_2d(temp);
//     }
//     new[j] = NULL;
//     free_tab_2d(my_env);
//     return new;
// }

// char    **append_env(char **my_env, char *s)
// {
//     char **new;
//     char **temp;
//     int i;

//     i = 0;
//     temp = ft_split(s, '=');
//     if (is_in_env(my_env, temp[0]))
//         my_env = supp_elem_env(my_env, temp[0]);
//     free_tab_2d(temp);
//     new = (char **)malloc(sizeof(char *) * (tab_2d_len(my_env) + 2));
//     if (!new)
//         return NULL;
//     while (my_env[i])
//     {
//         new[i] = ft_strdup(my_env[i]);
//         i++;
//     }
//     new[i] = ft_strdup(s);
//     i++;
//     new[i] = NULL;
//     free_tab_2d(my_env);
//     return new;
// }

int cmdlist_len(t_cmdlst *lst)
{
	int	cur;

	cur = 0;
	while (lst)
	{
		cur++;
		lst = lst->next;
	}
    return cur;
}

int    outlst_len(t_outlst *lst)
{
    int i;
    while (lst)
    {
        i++;
        lst = lst->next;
    }
    return i;
}

