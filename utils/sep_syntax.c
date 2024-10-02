/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_separator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:01:43 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/25 17:14:09 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_redircmp(char *s1, char *s2, int *i)
{
	int	c;
	int	k;

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

int	ft_pipe(t_vars *vars, int *i, t_list **comm)
{
	if (*i == 0 || vars->read[*i + 1] == '|')
		return (ft_error(comm, vars), -1);
	else
	{
		(*i)++;
		if (after_skip(vars->read, *i, PIP) == -1)
			return (ft_error(comm, vars), -1);
	}
	return (0);
}

int	ft_append(t_vars *vars, int *i, t_list **comm)
{
	if (ft_strlen(vars->read) == 2
		|| ((vars->read[*i + 2] && vars->read[*i + 2] == '>')
			|| vars->read[*i + 2] == '\0'))
		return (ft_error(comm, vars), -1);
	else
	{
		*i += 2;
		if (after_skip(vars->read, *i, RED_APPEND) == -1)
			return (ft_error(comm, vars), -1);
	}
	return (0);
}

int	ft_heredoc(t_vars *vars, int *i, t_list **comm)
{
	if (ft_strlen(vars->read) == 2)
		return (ft_error(comm, vars), -1);
	else
	{
		*i += 2;
		if (after_skip(vars->read, *i, HEREDOC) == -1)
			return (ft_error(comm, vars), -1);
	}
	return (0);
}

int	ft_redirec(t_vars *vars, int *i, t_list **comm, char c)
{
	if (ft_strlen(vars->read) == 1 || vars->read[*i + 1] == '\0')
		return (ft_error(comm, vars), -1);
	else
	{
		(*i)++;
		if (after_skip(vars->read, *i, c) == -1)
			return (ft_error(comm, vars), -1);
	}
	return (0);
}
