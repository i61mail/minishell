#include "../minishell.h"

int main()
{
    char *read;

    while (1)
    {
        read = readline("minishell> ");
        if (!read)
            break ;
		system(read);
    }
    return (0);
}   
