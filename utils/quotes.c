/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 08:07:31 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/23 18:07:39 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_digit(t_vars *vars, int *i, int *check)
{
	if (ft_isdigit(vars->read[*i]))
	{
		*check = 1;
		(*i)++;
	}
}

int	dollar(t_vars *vars, int *i, char **str_temp, t_env **envir)
{
	char	*temp;
	int		check;

	init_va(&check, &temp);
	if (vars->read[*i] == '$')
	{
		check_dollar(vars, i, str_temp);
		vars->start = *i;
		vars->len = count_dollar(vars->read, i);
		if (vars->len % 2 != 0)
			skip_digit(vars, i, &check);
		if (vars->len % 2 != 0 && check == 0)
			append_dollar2(vars, i, &temp, envir);
		else if (vars->len % 2 != 0 && check == 1)
			temp = ft_substr(vars->read, vars->start, vars->len - 1);
		else
			temp = ft_substr(vars->read, vars->start, vars->len);
		*str_temp = ft_strjoin(*str_temp, temp);
	}
	return (free(temp), 0);
}

int	double_quo(t_vars *vars, int *i, char **str_temp, t_env **envir)
{
	char	temp[2];

	temp[1] = '\0';
	while (vars->read[*i] && vars->read[*i] != 34)
	{
		if (vars->read[*i] == '$')
			dollar(vars, i, str_temp, envir);
		else if (vars->read[*i] != 34)
		{
			temp[0] = vars->read[*i];
			*str_temp = ft_strjoin(*str_temp, temp);
			if (!*str_temp)
				return (-1);
			(*i)++;
		}
	}
	if (vars->read[*i] == 34)
	{
		(*i) += 1;
		vars->bef_spac = *i;
	}
	return (0);
}

int	single_quo(t_vars *vars, int *i, char **str_temp)
{
	char	temp[2];

	temp[1] = '\0';
	if (vars->read[*i] == 39)
	{
		(*i)++;
		while (vars->read[*i] && vars->read[*i] != 39)
		{
			temp[0] = vars->read[*i];
			*str_temp = ft_strjoin(*str_temp, temp);
			if (!*str_temp)
				return (-1);
			(*i)++;
		}
		(*i)++;
	}
	return (0);
}

int	ft_arequotes(t_vars *vars, int *i, t_list **comm, t_env **envir)
{
	char	*str_temp;
	int		check;
	t_list	*curr;

	check = 0;
	curr = NULL;
	if (*i > 0 && !ft_isspace(vars->read[*i - 1])
		&& !ft_issep(vars->read[*i - 1]))
		*i = vars->befor_sing;
	while (vars->read[*i])
	{
		str_temp = NULL;
		if (before_quotes(vars, i, &str_temp) == -1)
			return (-1);
		check = dollar_quotes(vars, i, &str_temp, envir);
		if (check == -1)
			return (-1);
		replace_expand(curr, str_temp, comm);
		if (check == 2)
			break ;
	}
	return (0);
}
