/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:06:07 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/27 10:32:17 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_dollar(char *str, int *i)
{
	int	len;

	len = 0;
	while (str[*i] == '$')
	{
		(*i)++;
		len++;
	}
	return (len);
}

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

int	append_dollar2(t_vars *vars, int *i, char **temp, t_env **envir)
{
	if (!ft_isdigit(vars->read[*i]) && !ft_isalpha(vars->read[*i])
		&& vars->read[*i] != '_' && !ft_isquotes(vars->read[*i])
		&& vars->len > 1)
		*temp = ft_substr(vars->read, vars->start, vars->len);
	if (vars->len % 2 != 0 && vars->inside == 0 && !ft_isdigit(vars->read[*i])
		&& vars->read[*i] != '?' && !ft_isquotes(vars->read[*i])
		&& !ft_isalpha(vars->read[*i]) && vars->read[*i] != '_')
	{
		if (!*temp)
			*temp = ft_substr(vars->read, vars->start, vars->len);
	}
	else if (vars->inside == 1 && !ft_isdigit(vars->read[*i])
		&& vars->read[*i] != '?' && !ft_isalpha(vars->read[*i])
		&& vars->read[*i] != '_')
	{
		*temp = ft_substr(vars->read, vars->start, vars->len);
	}
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

int	append_dollar(t_vars *vars, int *i, char **temp, t_env **envir)
{
	if (!ft_isdigit(vars->read[*i]) && !ft_isalpha(vars->read[*i])
		&& vars->read[*i] != '_' && vars->read[*i] != '?')
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
