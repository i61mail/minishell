/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:03:29 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/27 17:46:14 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	address_quote(t_vars *vars, int *i, char **str_temp, t_env **envir)
{
	if (vars->read[*i] == '$')
		return (ft_dollar(vars, i, str_temp, envir));
	if (ft_isquotes(vars->read[*i]))
		return (2);
	return (0);
}

int	join_string(t_vars *vars, int *i, char **str_temp)
{
	char	temp[2];

	temp[1] = '\0';
	temp[0] = vars->read[*i];
	*str_temp = ft_strjoin(*str_temp, temp);
	if (!*str_temp)
		return (-1);
	(*i)++;
	return (0);
}

int	double_quo(t_vars *vars, int *i, char **str_temp, t_env **envir)
{
	while (vars->read[*i] && vars->read[*i] != 34)
	{
		if (vars->read[*i] == '$')
		{
			vars->inside = 1;
			if (*i > 0 && (ft_isalpha(vars->read[*i - 1])
					|| vars->read[*i - 1] == '_'
					|| (ft_isspace(vars->read[*i - 1]) && vars->inside == 0)))
				vars->flag_splite = SPLITED;
			dollar(vars, i, str_temp, envir);
			vars->inside = 0;
		}
		else if (vars->read[*i] != 34)
		{
			if (join_string(vars, i, str_temp) == -1)
				return (-1);
		}
	}
	if (vars->read[*i] == 34)
	{
		(*i) += 1;
		vars->bef_spac = *i;
	}
	return (0);
}
