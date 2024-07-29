#include "../minishell.h"

void	ft_error(t_list **comm)
{
	printf("bash: syntax error\n");
	ft_lstfree(comm);
	return ;
}

int	ft_check_type(char *read, int *i, int *type)
{
	int	c;
	
	c = *i;
	if (read[c] == '|')
		*type = PIP;
	else if (ft_redircmp(read, ">>", i) == 1)
		*type = RED_APPEND;
	else if (ft_redircmp(read, "<<", i) == 1)
		*type = HEREDOC;
	else if (read[c] == '<')
		*type = RED_IN;
	else if (read[c] == '>')
		*type = RED_OUT;
	else
		return (-1);
	return (0);
}

int	skip_space(char *str, char c, int red)
{
	int	i;

	i = 0;
	(void)red;
	(void)c;
	while (ft_isspace(str[i]))
		i++;
	return (0);
}

int	after_skip(char *str, int i)
{
	int check;

	check = 0;
	while (ft_isspace(str[i]))
	{
		check = 1;
		i++;
	}
	if ((str[i] == '\0' && check == 1) || (ft_issep(str[i]) && check == 1))
		return (-1);
	return (0);
}
