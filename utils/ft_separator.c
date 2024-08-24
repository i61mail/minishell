/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_separator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:01:43 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/24 17:03:27 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pipe(t_vars *vars, int *i, t_list **comm)
{
	if (*i == 0 || vars->read[*i + 1] == '|')
		return (ft_error(comm), -1);
	else
	{
		(*i)++;
		if (after_skip(vars->read, *i, PIP) == -1)
			return (ft_error(comm), -1);
	}
	return (0);
}

int	ft_append(t_vars *vars, int *i, t_list **comm)
{
	if (ft_strlen(vars->read) == 2
		|| ((vars->read[*i + 2] && vars->read[*i + 2] == '>')
			|| vars->read[*i + 2] == '\0'))
		return (ft_error(comm), -1);
	else
	{
		*i += 2;
		if (after_skip(vars->read, *i, RED_APPEND) == -1)
			return (ft_error(comm), -1);
	}
	return (0);
}

int	ft_heredoc(t_vars *vars, int *i, t_list **comm)
{
	if (ft_strlen(vars->read) == 2
		|| ((vars->read[*i + 2] && vars->read[*i + 2] == '<')
			|| vars->read[*i + 2] == '\0'))
		return (ft_error(comm), -1);
	else
	{
		*i += 2;
		if (after_skip(vars->read, *i, HEREDOC) == -1)
			return (ft_error(comm), -1);
	}
	return (0);
}

int	ft_redirec(t_vars *vars, int *i, t_list **comm, char c)
{
	if (ft_strlen(vars->read) == 1 || vars->read[*i + 1] == '\0')
		return (ft_error(comm), -1);
	else
	{
		(*i)++;
		if (after_skip(vars->read, *i, c) == -1)
			return (ft_error(comm), -1);
	}
	return (0);
}
