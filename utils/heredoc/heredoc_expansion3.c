/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:37:25 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/30 18:11:48 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	heredoc_single(t_vars *vars, int *i, char **str_temp)
{
	char	temp[2];

	temp[1] = '\0';
	while (vars->read[*i] && vars->read[*i] != 39)
	{
		temp[0] = vars->read[*i];
		*str_temp = ft_strjoin(*str_temp, temp);
		if (!*str_temp)
			return (-1);
		(*i)++;
	}
	return (0);
}

int	heredoc_double(t_vars *vars, int *i, char **str_temp)
{
	char	temp[2];

	temp[1] = '\0';
	if (vars->read[*i] == 34)
		(*i)++;
	while (vars->read[*i] && vars->read[*i] != 34)
	{
		temp[0] = vars->read[*i];
		*str_temp = ft_strjoin(*str_temp, temp);
		if (!*str_temp)
			return (-1);
		(*i)++;
	}
	return (0);
}

int	heredoc_char(t_vars *vars, int *i, char **str_temp)
{
	char	temp[2];

	temp[1] = '\0';
	while (vars->read[*i] && !ft_issep(vars->read[*i])
		&& !ft_isquotes(vars->read[*i]) && !ft_isspace(vars->read[*i])
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

void	isthere_quotes(char *str, int *i, int *var)
{
	int	k;

	k = *i;
	while (str[k] && !ft_isspace(str[k]) && !ft_issep(str[k]))
	{
		if (ft_isquotes(str[k]))
			*var = 1;
		k++;
	}
	if (*var == 1)
		return ;
}

void	add_to_temp_here(char **str_temp, int *i, char *line)
{
	char	temp[2];

	temp[1] = '\0';
	temp[0] = line[*i];
	*str_temp = ft_strjoin(*str_temp, temp);
}
