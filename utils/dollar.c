/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:06:07 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/23 18:07:00 by isrkik           ###   ########.fr       */
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

int	check_isthere(t_vars *vars, int *b, int i, int *check)
{
	if (vars->read[*b] && vars->read[*b] == 34 && *check == 0 && i > *b)
	{
		*check = 1;
		(*b)++;
	}
	while (vars->read[*b] && *check == 1 && (ft_isalpha(vars->read[*b])
			|| ft_isdigit(vars->read[*b])
			|| vars->read[*b] == '_' || ft_isspace(vars->read[*b])))
	{
		(*b)++;
		if (vars->read[*b] && vars->read[*b] == '$')
			return (1);
	}
	return (0);
}

int	isthere(t_vars *vars, int *i)
{
	int	b;
	int	check;

	check = 0;
	b = vars->bef_spac;
	while (vars->read[b] && b != *i)
	{
		if (check_isthere(vars, &b, *i, &check) == 1)
			return (1);
		if (vars->read[b] && (vars->read[b] == 34 || (!ft_isdigit(vars->read[b]) && !ft_isalpha(vars->read[b]) && vars->read[b] != '?')) && check == 1 && b > *i)
			return (1);
		if (vars->read[b] && vars->read[b] == 34 && check == 1)
			return (0);
		if (vars->read[b] && vars->read[b] == 39 && check == 1)
			return (1);
		b++;
		if (b > *i + 1)
			return (0);
	}
	if (vars->read[b] && b == *i && (!ft_isquotes(vars->read[b + 1])
			&& vars->read[b + 1] != '_' && !ft_isdigit(vars->read[b + 1])
			&& !ft_isalpha(vars->read[b + 1])))
		return (1);
	return (0);
}

int	ft_onedollar(char *str, int *i)
{
	if (str[*i] && str[*i] == 34)
		(*i)++;
	if (str[*i] && str[*i] == '$')
	{
		if (str[*i + 1] == 34)
			return (1);
		else
			return (0);
	}
	return (0);
}

void	check_dollar(t_vars *vars, int *i, char **str_temp)
{
	if (vars->read[*i + 1] != '$' && !ft_isdigit(vars->read[*i + 1])
		&& !ft_isalpha(vars->read[*i + 1]) && vars->read[*i + 1] != '_' && vars->read[*i + 1] != '?')
	{
		if (*i > 0 && vars->read[*i] && (vars->read[*i + 1] == '\0'
				|| isthere(vars, i)))
			*str_temp = ft_strjoin(*str_temp, "$\0");
		else if (*i > 0 && vars->read[*i] && ft_isquotes(vars->read[*i + 1]
				&& isthere(vars, i)))
			*str_temp = ft_strjoin(*str_temp, "$\0");
	}
}
