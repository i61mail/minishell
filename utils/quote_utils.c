/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: i61mail <i61mail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 09:02:03 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/21 11:37:21 by i61mail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_dollar(char *str, int *i)
{
	int	k;

	k = 0;
	(*i)--;
	while (str[*i] == '$')
	{
		(*i)++;
		k++;
	}
	if (k % 2 == 0)
		return (k);
	else
		return (k - 1);
	return (0);
}

int	quotes(t_vars *vars, int *i, t_list **comm, t_env **envir)
{
	if (ft_isquotes(vars->read[*i]))
	{
		if (even_odd(vars->read) == 0)
		{
			ft_error(comm, vars);
			return (-1);
		}
		ft_arequotes(vars, i, comm, envir);
	}
	return (0);
}

int	after_skip(char *str, int i, char c)
{
	while (ft_isspace(str[i]))
		i++;
	if (c == HEREDOC)
	{
		if (str[i] == '\0' || ft_issep(str[i]))
			return (-1);
	}
	else if (c == PIP)
	{
		if (str[i] == '\0')
			return (-1);
	}
	else if (c == RED_OUT || c == RED_IN)
	{
		if (str[i] == '\0' || ft_issep(str[i]))
			return (-1);
	}
	else if (c == RED_APPEND)
	{
		if (str[i] == '\0' || ft_issep(str[i]))
			return (-1);
	}
	return (0);
}

void	add_before(char **str_temp, t_vars *vars, int *i)
{
	*str_temp = ft_strdup(vars->befor);
	vars->befor = NULL;
	*i = vars->befo_qu;
}

int	before_quotes(t_vars *vars, int *i, char **str_temp, t_env **envir)
{
	char	temp[2];

	temp[1] = '\0';
	if (!vars->befor)
	{
		while (vars->read[*i] && !ft_isquotes(vars->read[*i]))
		{
			if (vars->read[*i] == '$')
			{
				if (dollar(vars, i, str_temp, envir) == -1)
					return (-1);
			}
			else
			{
				temp[0] = vars->read[*i];
				*str_temp = ft_strjoin(*str_temp, temp);
				(*i)++;
			}
		}
	}
	else
		add_before(str_temp, vars, i);
	return (0);
}
