/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:03:29 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/22 15:11:10 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	append_dollar2(t_vars *vars, int *i, char **temp, t_env **envir)
{
	if (!ft_isdigit(vars->read[*i]) && !ft_isalpha(vars->read[*i])
		&& vars->read[*i] != '_' && vars->len > 1)
		*temp = ft_substr(vars->read, vars->start, vars->len);
	else
		*temp = ft_substr(vars->read, vars->start, vars->len - 1);
	expanding(vars, i, temp, envir);
	return (0);
}

int	join_afterdollar(t_vars *vars, int *i, char **str_temp)
{
	char	stemp[2];

	stemp[1] = '\0';
	while (vars->read[*i] && !ft_isspace(vars->read[*i])
		&& !ft_issep(vars->read[*i]) && vars->read[*i] != '$'
		&& !ft_isquotes(vars->read[*i]))
	{
		stemp[0] = vars->read[*i];
		*str_temp = ft_strjoin(*str_temp, stemp);
		if (!*str_temp)
			return (-1);
		(*i)++;
	}
	return (0);
}

int	address_quote(t_vars *vars, int *i, char **str_temp, t_env **envir)
{
	if (vars->read[*i] == '$')
		return (ft_dollar(vars, i, str_temp, envir));
	if (ft_isquotes(vars->read[*i]))
		return (free(*str_temp), 2);
	return (0);
}

void	initi_vars(int *check, char **temp)
{
	*check = 0;
	*temp = NULL;
}

int	append_dollar(t_vars *vars, int *i, char **temp, t_env **envir)
{
	if (!ft_isdigit(vars->read[*i]) && !ft_isalpha(vars->read[*i])
		&& vars->read[*i] != '_')
	{
		*temp = ft_substr(vars->read, vars->start, vars->len);
		if (!*temp)
			return (-1);
	}
	else
	{
		*temp = ft_substr(vars->read, vars->start, vars->len - 1);
		if (!*temp)
			return (-1);
	}
	expanding(vars, i, temp, envir);
	return (0);
}
