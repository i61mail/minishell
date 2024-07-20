#include "../minishell.h"

int	even_odd(char *read, bool what)
{
	int	i;
	int	check;

	check = 0;
	i = 0;
	while (read[i])
	{
		if (what == true)
		{
			if (read[i] == 34)
				check += 1;
		}
		else if (what == false)
		{
			if (read[i] == 39)
				check += 1;
		}
		i++;
	}
	if (check % 2 == 0)
	{
		if (read[0] == 34 && read[i - 1] != 34)
			return (0);
		else if (read[0] == 39 && read[i - 1] != 39)
			return (0);
		return (1);
	}
	return (0);
}
