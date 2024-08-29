/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arewhat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:52:49 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/24 16:33:34 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_dollar(t_vars *vars, int *i, char **str_temp, t_env **envir)
{
	char	*temp;
	int		check;

	initi_vars(&check, &temp);
	if (vars->read[*i] == '$')
	{
		vars->start = *i;
		vars->len = count_dollar(vars->read, i);
		if (vars->len % 2 != 0)
			skip_digit(vars, i, &check);
		if (vars->len % 2 != 0 && check == 0)
		{
			append_dollar(vars, i, &temp, envir);
		}
		else if (vars->len % 2 != 0 && check == 1)
			temp = ft_substr(vars->read, vars->start, vars->len - 1);
		else
			temp = ft_substr(vars->read, vars->start, vars->len);
		*str_temp = ft_strjoin(*str_temp, temp);
		free(temp);
		if (join_afterdollar(vars, i, str_temp) == -1)
			return (-1);
		if (address_quote(vars, i, str_temp, envir) == 2)
			return (2);
	}
	return (0);
}

int	adding(t_vars *vars, int *i, char **str_temp)
{
	char	temp[2];

	temp[1] = '\0';
	if (!ft_issep(vars->read[*i]) && !ft_isspace(vars->read[*i])
		&& !ft_isquotes(vars->read[*i]) && vars->read[*i] != '$')
	{
		temp[0] = vars->read[*i];
		*str_temp = ft_strjoin(*str_temp, temp);
		(*i)++;
	}
	return (0);
}

static void	init_vars(char **str_temp, t_list **curr, int *hold)
{
	*hold = 0;
	*curr = NULL;
	*str_temp = ft_strdup("");
	if (!str_temp)
		return ;
}

int	ft_arealpha(t_vars *vars, int *i, t_list **comm, t_env **envir)
{
	char	*str_temp;
	t_list	*curr;
	int		hold;
	char	temp[2];

	init_vars(&str_temp, &curr, &hold);
	temp[1] = '\0';
	vars->catsh = *i;
	vars->befor_sing = *i;
	while (vars->read[*i])
	{
		if (!ft_issep(vars->read[*i]) && !ft_isspace(vars->read[*i])
			&& !ft_isquotes(vars->read[*i]) && vars->read[*i] != '$')
		{
			temp[0] = vars->read[*i];
			str_temp = ft_strjoin(str_temp, temp);
			(*i)++;
		}
		else
		{
			if (vars->read[*i] == '$')
			{
				hold = ft_dollar(vars, i, &str_temp, envir);
				if (hold == 2)
					return (2);
				replace_expand(curr, str_temp, comm, 0);
				return (0);
			}
			else
				break ;
		}
	}
	if (vars->read[*i] && ft_isquotes(vars->read[*i]))
		return (free(str_temp), 2);
	if (ft_token(vars, *i, comm, COMM) == -1)
		return (-1);
	return (free(str_temp), 0);
}
