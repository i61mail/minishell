#include "../minishell.h"

int	ft_issingle(char *read, int *i)
{
	while (read[*i])
	{
		if (read[*i] == 39)
		{
			(*i)++;
			ft_issingle(read, i);
		}
		else
			break ;
	}
	return (0);
}
