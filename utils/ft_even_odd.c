#include "../minishell.h"

int	even_odd(char *read)
{
	int	i;
	int	check;
	int	sing;

	sing = 0;
	check = 0;
	i = 0;
	while (read[i])
	{
		if (read[i] == 34 && sing == 0)
		{
			if (check >= 1)
				check = 0;
			else
				check += 1;
		}
		else if (read[i] == 39 && check == 0)
		{
			if (sing >= 1)
				sing = 0;
			else
				sing += 1;
		}
		i++;
	}
	if (check % 2 == 0 && sing % 2 == 0)
		return (1);
	return (0);
}
