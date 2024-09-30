/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_delimiter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:33:21 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/30 18:18:50 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	heredoc_count_dollar(char *line, int *i, char **str_temp, int var)
{
	int		len;
	int		b;

	len = 0;
	b = *i;
	while (line[b] && line[b] == '$')
	{
		b++;
		len++;
	}
	if (len == 1 && line[b] && ft_isquotes(line[b]))
	{
		(*i)++;
		return (0);
	}
	if (len % 2 != 0 && len > 1 && var == 1)
		(*i)++;
	while (line[*i] && line[*i] == '$')
	{
		if (len % 2 == 0 || len % 2 != 0)
			add_to_temp_here(str_temp, i, line);
		(*i)++;
	}
	return (0);
}

void	isquoted(t_vars *vars, char **str_temp, t_list **comm)
{
	vars->del_type = HEREDOC_DEL_Q;
	vars->token = ft_strdup(*str_temp);
	replace_expand(*str_temp, comm, HEREDOC_DEL_Q);
}

void	isunquoted(t_vars *vars, char **str_temp, t_list **comm)
{
	vars->del_type = HEREDOC_DEL_U;
	vars->token = ft_strdup(*str_temp);
	replace_expand(*str_temp, comm, HEREDOC_DEL_U);
}

static void	init_vars(char **str_temp, int *var)
{
	*str_temp = NULL;
	*var = 0;
}

int	heredoc_delimiter(t_vars *vars, int *i, t_list **comm)
{
	char	*str_temp;
	int		var;

	init_vars(&str_temp, &var);
	if (even_odd(vars->read) == 0)
		return (ft_error(comm, vars), -1);
	isthere_quotes(vars->read, i, &var);
	while (vars->read[*i] && !ft_isspace(vars->read[*i])
		&& !ft_issep(vars->read[*i]))
	{
		if (vars->read[*i] && vars->read[*i] == 34)
			add_to_str_temp(vars, i, &str_temp, 0);
		if (vars->read[*i] && vars->read[*i] == 39)
			add_to_str_temp(vars, i, &str_temp, 1);
		if (vars->read[*i] && vars->read[*i] == '$')
			heredoc_count_dollar(vars->read, i, &str_temp, var);
		if (vars->read[*i] && !ft_issep(vars->read[*i])
			&& !ft_isquotes(vars->read[*i]))
			heredoc_char(vars, i, &str_temp);
	}
	if (var == 1)
		isquoted(vars, &str_temp, comm);
	else
		isunquoted(vars, &str_temp, comm);
	return (0);
}
