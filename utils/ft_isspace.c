#include "../minishell.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v')
		return (1);
	return (0);
}
