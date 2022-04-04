# include "../include/minishell.h"

char **append_tab_2d(char **tab, char *s)
{
    int i;
    char **new;

    i = 0;
    new = (char **)malloc(sizeof(char *) * (tab_2d_len(tab) + 2));
    if (!new)
        return NULL;
    while (tab[i])
    {
        new[i] = ft_strdup(tab[i]);
        i++;
    }
    new[i] = ft_strdup(s);
    i++;
    new[i] = NULL;
    free_tab_2d(tab);
    return new;
}

char **supp_last_elem_tab2d(char **tab)
{
    char **new;
    int len;
    int i;

    i = 0;
    len = tab_2d_len(tab);
    new = (char **)malloc(sizeof(char *) * (tab_2d_len(tab)));
    if (!new)
        return NULL;
    while (i < len - 1)
    {
        new[i] = ft_strdup(tab[i]);
        i++;
    }
    new[i] = NULL;
    free_tab_2d(tab);
    return new;
}

char *concat_path(char **tab, char *str)
{
    char *s;
    int i;
    int j;

    i = 0;
    s = ft_strdup(str);
    while(tab[i])
    {
        s = ft_strjoin(s, "/");
        s = ft_strjoin(s, tab[i]);
        i++;
    }
    return s;
}