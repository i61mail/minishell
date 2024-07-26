#include "../minishell.h"

int	ft_pipe(t_vars *vars, int *i, t_list **comm)
{
	if (*i == 0 || vars->read[*i + 1] == '|')
	{
		ft_error(comm);
		return (-1);
	}
	else if (skip_space(vars->read, '|', 0) == -1)
	{
		ft_error(comm);
		return (-1);
	}
	else
	{
		(*i)++;
		if (after_skip(vars->read, *i) == -1)
		{
			ft_error(comm);
			return (-1);
		}
	}
	return (0);
}


int	ft_append(t_vars *vars, int *i, t_list **comm)
{
	if (ft_strlen(vars->read) == 2 || ((vars->read[*i + 2] && vars->read[*i + 2] == '>')
		|| vars->read[*i + 2] == '\0'))
	{
		ft_error(comm);
		return (-1);
	}
	else if (skip_space(vars->read, '>', 2) == -1 )
	{
		ft_error(comm);
		return (-1);
	}
	else
	{
		*i += 2;
		if (after_skip(vars->read, *i) == -1)
		{
			ft_error(comm);
			return (-1);
		}
	}
	return (0);
}

int ft_heredoc(t_vars *vars, int *i, t_list **comm)
{
	if (ft_strlen(vars->read) == 2 || ((vars->read[*i + 2] && vars->read[*i + 2] == '<')
		|| vars->read[*i + 2] == '\0'))
	{
		ft_error(comm);
		return (-1);
	}
	else if (skip_space(vars->read, '<', 2) == -1)
	{
		ft_error(comm);
		return (-1);
	}
	else
	{
		*i += 2;
		if (after_skip(vars->read, *i) == -1)
		{
			ft_error(comm);
			return (-1);
		}
	}
	return (0);
}

int	ft_redirec(t_vars *vars, int *i, char c, t_list **comm)
{
	if (ft_strlen(vars->read) == 1 || vars->read[*i + 1] == '\0')
	{
		ft_error(comm);
		return (-1);
	}
	else if (skip_space(vars->read, c, 1) == -1)
	{
		ft_error(comm);
		return (-1);
	}
	else
	{
		(*i)++;
		if (after_skip(vars->read, *i) == -1)
		{
			ft_error(comm);
			return (-1);
		}
	}
	return (0);
}
