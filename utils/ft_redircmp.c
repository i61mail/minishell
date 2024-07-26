#include "../minishell.h"

int	ft_redircmp(char *s1, char *s2, int *i)
{
	int c;
	int k;

	k = 0;
	c = *i;
	while (s2[k])
	{
		if (s1[c] == s2[k])
		{
			c++;
			k++;
		}
		else
			return (-1);
	}
	return (1);
}
