/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:12:05 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/25 16:32:57 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_arespace(t_vars *vars, int *i)
{
	vars->bef_spac = *i;
	while (vars->read[*i])
	{
		if (ft_isspace(vars->read[*i]))
			(*i)++;
		else
			break ;
	}
	return (0);
}

int	ft_aresep3(t_vars *vars, int *i, int type, t_list **comm)
{
	int	check;

	check = 0;
	if (type == RED_IN || type == RED_OUT)
	{
		vars->catsh = *i;
		if (type == 1)
		{
			check = ft_redirec(vars, i, comm, RED_IN);
			if (check == 2)
				return (2);
			else if (check == -1)
				return (-1);
		}
		else
		{
			vars->check_ambiguous = 1;
			check = ft_redirec(vars, i, comm, RED_OUT);
			if (check == 2)
				return (2);
			else if (check == -1)
				return (-1);
		}
	}
	return (0);
}

int	ft_aresep2(t_vars *vars, int *i, int type, t_list **comm)
{
	int	check;

	check = 0;
	if (type == RED_APPEND)
	{
		vars->check_ambiguous = 1;
		vars->catsh = *i;
		check = ft_append(vars, i, comm);
		if (check == 2)
			return (2);
		else if (check == -1)
			return (-1);
	}
	else if (type == HEREDOC)
	{
		vars->catsh = *i;
		check = ft_heredoc(vars, i, comm);
		if (check == 2)
			return (2);
		else if (check == -1)
			return (-1);
	}
	if (ft_aresep3(vars, i, type, comm) == -1)
		return (-1);
	return (0);
}

int	is_heredoc(t_vars *vars, int *i, t_list **comm, t_env **envir)
{
	while (ft_isspace(vars->read[*i]))
		(*i)++;
	if (ft_isquotes(vars->read[*i]) || !ft_issep(vars->read[*i]))
	{
		if (heredoc_delimiter(vars, i, comm) == -1)
			return (-1);
		process_heredoc(vars, envir);
	}
	return (0);
}

int	ft_aresep(t_vars *vars, int *i, t_list **comm, t_env **envir)
{
	int	type;
	int	check;

	type = 0;
	if (ft_check_type(vars->read, i, &type) == -1)
		return (ft_error(comm, vars), -1);
	if (type == PIP)
	{
		vars->catsh = *i;
		check = ft_pipe(vars, i, comm);
		if (check == 2)
			return (2);
		else if (check == -1)
			return (-1);
	}
	if (ft_aresep2(vars, i, type, comm) == -1)
		return (-1);
	if (ft_token(vars, *i, comm, type) == -1)
		return (-1);
	if (type == HEREDOC)
	{
		if (is_heredoc(vars, i, comm, envir) == -1)
			return (-1);
	}
	return (0);
}
