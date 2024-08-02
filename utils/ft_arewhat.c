/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arewhat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:52:49 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/02 16:54:14 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_arealpha(t_vars *vars, int *i, t_list **comm)
{
	vars->catsh = *i;
	while (vars->read[*i])
	{
		if (!ft_issep(vars->read[*i]) && !ft_isspace(vars->read[*i])
			&& !ft_isquotes(vars->read[*i]))
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

int	ft_arespace(char *read, int *i)
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

static int	ft_aresep3(t_vars *vars, int *i, int type, t_list **comm)
{
	int	check;

	check = 0;
	if (type == 1 || type == 2) //redirection '<' && '>'
	{
		vars->catsh = *i;
		if (type == 1)
		{
			check = ft_redirec(vars, i, '<', comm);
			if (check == 2)
				return (2);
			else if (check == -1)
				return (-1);
		}
		else
		{
			check = ft_redirec(vars, i, '>', comm);
			if (check == 2)
				return (2);
			else if (check == -1)
				return (-1);
		}
	}
	return (0);
}

static int	ft_aresep2(t_vars *vars, int *i, int type, t_list **comm)
{
	int	check;

	check = 0;
	if (type == 3) //append >>
	{
		vars->catsh = *i;
		check = ft_append(vars, i, comm);
		if (check == 2)
			return (2);
		else if (check == -1)
			return (-1);
	}
	else if (type == 4) // heredoc <<
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

int	ft_aresep(t_vars *vars, int *i, t_list **comm)
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
	if (ft_aresep2(vars, i, type, comm) == -1)
		return (-1);
	if (ft_token(vars, *i, comm, type) == -1)
		return (-1);
	return (0);
}

// int	ft_count_dollar(char *str, int *i)
// {
// 	int	k;

// 	k = 0;
// 	while (str[*i] == '$')
// 	{
// 		(*i)++;
// 		k++;
// 	}
// 	if (k % 2 == 0)
// 		return (k);
// 	else
// 		return (k - 1);
// 	return (0);
// }

// int	ft_arequotes(t_vars *vars, int *i, t_list **comm, int type)
// {
// 	return (0);
// }
