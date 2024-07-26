#include "../minishell.h"

void	ft_error(void)
{
	printf("bash: syntax error near unexpected token `|'\n");
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

int	skip_space(char *str, int sep)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
	{
		i++;
		if (str[i] == sep)
			return (-1);
	}
	return (0);
}

int	ft_pipe(t_vars *vars, int *i)
{
	if (*i == 0 || vars->read[*i + 1] == '|')
	{
		ft_error();
		return (-1);
	}
	else if (skip_space(vars->read, PIP) == -1)
	{
		ft_error();
		return (-1);
	}
	else
		(*i)++;
	return (0);
}

int	ft_append(t_vars *vars, int *i)
{
	if (ft_strlen(vars->read) == 2 || (vars->read[*i + 2] && vars->read[*i + 2] == '>'))
	{
		ft_error();
		return (-1);
	}
	else if (skip_space(vars->read, RED_APPEND) == -1)
	{
		ft_error();
		return (-1);
	}
	else
		*i += 2;
	return (0);
}

int ft_heredoc(t_vars *vars, int *i)
{
	if (ft_strlen(vars->read) == 2 || (vars->read[*i + 2] && vars->read[*i + 2] == '<'))
	{
		ft_error();
		return (-1);
	}
	else if (skip_space(vars->read, HEREDOC) == -1)
	{
		ft_error();
		return (-1);
	}
	else
		*i += 2;
	return (0);
}