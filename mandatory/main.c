#include "../minishell.h"

int    ft_arealpha(char *read, int *i, t_list **comm)
{
    int catsh;
    int j;
    char    *command;

    j = 0;
    catsh = *i;
    while (read[*i])
    {
        if ((read[*i] >= 'a' && read[*i] <= 'z') || (read[*i] >= 'A' && read[*i] <= 'Z'))
            (*i)++;
        else
            break ;
    }
    command = ft_substr(read, catsh, *i - catsh);
    if (!command)
        return (-1);
    *comm = ft_lstnew(command);
    if (!*comm)
    {
        free(command);
        return (-1);
    }
    printf("%s\n", (*comm)->content);
    return (0);
}

int ft_arespace(char *read, int *i)
{
    while (read[*i])
    {
        if (ft_isspace(read[*i]))
            (*i)++;
        else
            break ;
    }
    return (0);
}

int    ft_pars_comm(char *read, t_list **comm)
{
    int i;

    i = 0;
    if (read[i] != '\0')
    {
        if (ft_isalpha(read[i]))
            ft_arealpha(read, &i, comm);
        if (ft_isspace(read[i]))
            ft_arespace(read, &i);
        else
            return (-1);
    }
    return (0);
}

int main(int ac, char **av)
{
    char *read;
    t_list  *comm;
    (void)av;

    while (1)
    {
        if (ac == 1)
        {
            read = readline("minishell> ");
            if (!read)
                break ;
            ft_pars_comm(read, &comm);
        }
        else
            break ;
    }
    return (0);
}   
