#include "../minishell.h"

int    ft_arealpha(t_vars *vars, int *i, t_list **comm)
{
	vars->catsh = *i;
	while (vars->read[*i])
	{
		if (!ft_issep(vars->read[*i]) && !ft_isspace(vars->read[*i]) && !ft_isquotes(vars->read[*i]))
			(*i)++;
		else
			break ;
	}
	if (ft_isquotes(vars->read[*i]))
		return (2);
	if (ft_token(vars, *i, comm, COMM) == -1)
		return (-1);
	return (0);
}

int ft_arespace(char *read, int *i)
{
	while (read[*i])
	{
		if (ft_isspace(read[*i]))
			(*i)++;
		else
			break ;
	}
	return (0);
}

static int	ft_aresep2(t_vars *vars, int *i, int type, t_list **comm)
{
	if (type == 4) // heredoc <<
	{
		vars->catsh = *i;
		if (ft_heredoc(vars, i, comm) == -1)
			return (-1);
	}
	else if (type == 1 || type == 2) //redirection '<' && '>'
	{
		vars->catsh = *i;
		if (type == 1)
		{
			if (ft_redirec(vars, i, '<', comm) == -1)
				return (-1);
		}
		else
		{
			if (ft_redirec(vars, i, '>', comm) == -1)
				return (-1);
		}
	}
	return (0);
}

int ft_aresep(t_vars *vars, int *i, t_list **comm)
{
	int	type;
	int	check;

	type = 0;
	if (ft_check_type(vars->read, i, &type) == -1)
	{
		ft_error(comm);
		return (-1);
	}
	if (type == 5) //pipe
	{
		vars->catsh = *i;
		check = ft_pipe(vars, i, comm);
		if (check == 2)
			return (2);
		else if (check == -1)
			return (-1);
	}
	else if (type == 3) //append >>
	{
		vars->catsh = *i;
		if (ft_append(vars, i, comm) == -1)
			return (-1);
	}
	if (ft_aresep2(vars, i, type, comm) == -1)
		return (-1);
	if (ft_token(vars, *i, comm, type) == -1)
		return (-1);
	return (0);
}

int	ft_arequotes(t_vars *vars, int *i, t_list **comm, int type)
{
	int	check;
	
	check = 0;
	while (vars->read[*i])
	{
		(*i)++;
		if (ft_isquotes(vars->read[*i]) || vars->read[*i] == '\0' || ft_isspace(vars->read[*i]))
		{
			if (ft_isquotes(vars->read[*i]))
				check = 1;
			if (vars->read[*i] == '\0' || (ft_isspace(vars->read[*i]) && check == 1) || (ft_isspace(vars->read[*i + 1]) && check == 1) || vars->read[*i + 1] == '\0')
			{
				check = 0;
				if (ft_token(vars, *i, comm, type) == -1)
				{
					ft_error(comm);
					return (-1);
				}
				if (vars->read[*i] != '\0')
					(*i)++;
				break ;
			 }
		}
	}
	return (0);
}
