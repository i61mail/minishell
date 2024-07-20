#include "../minishell.h"

int	ft_isdouble(char *read, int *i)
{
	while (read[*i])
	{
		if (read[*i] == 34)
		{
			(*i)++;
			ft_isdouble(read, i);
		}
		else
			break ;
	}
	return (0);
}
