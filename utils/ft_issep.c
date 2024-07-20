#include "../minishell.h"

int ft_issep(int c)
{
    if (c == '<' || c == '>' || c == '|')
        return (1);
    return (0);
}