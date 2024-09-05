/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 09:02:03 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/05 16:34:24 by isrkik           ###   ########.fr       */
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

int	before_quotes(t_vars *vars, int *i, char **str_temp)
{
	char	temp[2];

	temp[1] = '\0';
	while (vars->read[*i] && !ft_isquotes(vars->read[*i])
		&& vars->read[*i] != '$')
	{
		temp[0] = vars->read[*i];
		*str_temp = ft_strjoin(*str_temp, temp);
		if (!*str_temp)
			return (-1);
		(*i)++;
	}
	return (0);
}
