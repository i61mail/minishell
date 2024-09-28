/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 08:07:31 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/28 16:55:58 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_isempty(t_vars *vars, int *i)
{
	if (vars->read[*i] == '\0')
	{
		vars->not_pass = 1;
		return ;
	}
	else if (ft_isquotes(vars->read[*i]))
		vars->not_pass = 0;
	else
		vars->not_pass = 1;
}

void	init_v(int *check, char **temp)
{
	*check = 0;
	*temp = NULL;
}

int	single_quo(t_vars *vars, int *i, char **str_temp)
{
	char	temp[2];

	temp[1] = '\0';
	if (vars->read[*i] == 39)
	{
		vars->quoted = 1;
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

static void	init_va(char **str_temp, int *check)
{
	*check = 0;
	*str_temp = NULL;
}

int	ft_arequotes(t_vars *vars, int *i, t_list **comm, t_env **envir)
{
	char	*str_temp;
	int		check;

	init_va(&str_temp, &check);
	if (*i > 0 && !ft_isspace(vars->read[*i - 1])
		&& !ft_issep(vars->read[*i - 1]))
		*i = vars->befor_sing;
	vars->inside = 0;
	if (before_quotes(vars, i, &str_temp, envir) == -1)
		return (-1);
	while (vars->read[*i])
	{
		vars->inside = 0;
		check = dollar_quotes(vars, i, &str_temp, envir);
		if (check == -1)
			return (-1);
		if (vars->flag_splite == SPLITED)
			replace_expand(str_temp, comm, SPLITED);
		else
			replace_expand(str_temp, comm, 0);
		if (check == 2)
			break ;
	}
	return (0);
}
