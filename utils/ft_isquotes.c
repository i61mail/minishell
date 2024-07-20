#include "../minishell.h"

int		ft_isquotes(int c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}