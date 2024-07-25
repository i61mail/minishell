#include "../minishell.h"

void	ft_error(void)
{
	printf("bash: syntax error near unexpected token `|'\n");
	return ;
}

void	ft_check_type(char *read, int *i, int *type)
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
}

int	ft_pipe(t_vars *vars, int *i)
{
	int	c;
	int	stop;

	// vars->catsh = *i;
	stop = 0;
	c = *i;
	if (*i == 0 || vars->read[*i + 1] == '|' || vars->read[*i + 1] == '\0')
	{
		ft_error();
		return (-1);
	}
	while (vars->read[*i + 1])
	// while (ft_isspace(vars->read[*i + 1]))
	// 	c++;
	// if (ft_issep(vars->read[c + 1]))
	// {
	// 	c += 2;
	// 	if (ft_append(vars, &c, false) == -1)
	// 		return (-1);
	// 	// while (ft_issep(vars->read[c]))
	// 	// {
	// 	// 	stop++;
	// 	// 	c++;
	// 	// }
	// 	// if (stop > 1 || vars->read[c] == '\0')
	// 	// {
	// 	// 	ft_error();
	// 	// 	return(-1);
	// 	// }
	// }
	// else
	// 	(*i)++;
	return (0);
}

int	ft_append(t_vars *vars, int *i, bool what)
{
	// int	c;

	(void)what;
	// c = *i;
	printf("%d\n", *i);
	if (ft_strlen(vars->read) == 2 || ft_issep(vars->read[*i + 2]) || vars->read[*i + 1] == '\0')
	{
		ft_error();
		return (-1);
	}
	// if (vars->read[c + 2] != '\0')
		// c += 2; 
	// while (ft_isspace(vars->read[c]))
	// 	c++;
	while (!ft_isspace(vars->read[*i + 1]) && !ft_isalpha(vars->read[*i + 1]))
		(*i)++;
	// if (vars->read[c] == '|')
	// 	ft_pipe(vars, &c);
	// else
	// 	*i = c;
	return (0);
}