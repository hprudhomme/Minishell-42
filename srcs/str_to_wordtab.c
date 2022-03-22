# include "../include/minishell.h"

int is_alpha_num(char c)
{
    return ((c >= '0' && c <= '9') ||
            (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z'));
}

unsigned int count_words(const char * str)
{
    unsigned int i = 0;
    unsigned int nb_words = 0;

    while (str[i])
    {
        while (str[i] && !is_alpha_num(str[i]))
            i++;
        if (str[i])
            nb_words++;
        while (str[i] && is_alpha_num(str[i]))
            i++;
    }
	return nb_words;
}

char **str_to_wordtab(char *str)
{
    unsigned int nb_words = count_words(str);
    char ** array = malloc(sizeof(*array) * (nb_words + 1));
    unsigned int i = 0;
    unsigned int j = 0;

    while (str[i])
    {
        while (str[i] && !(is_alpha_num(str[i]) || str[i] == '-' || str[i] == '|'))
            str[i++] = '\0';
        if (str[i])
            array[j++] = &(str[i]);
        while (str[i] && (is_alpha_num(str[i]) || str[i] == '-' || str[i] == '|'))
            i++;
    }
    array[j] = 0;
    return array;
}
