/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:52:49 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/25 17:51:17 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	init_vars(int *check, char **temp)
{
	*check = 0;
	*temp = NULL;
}

int	dollar(t_vars *vars, int *i, char **str_temp, t_env **envir)
{
	char	*temp;
	int		check;

	init_vars(&check, &temp);
	if (vars->read[*i] == '$')
	{
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
		if (temp)
			*str_temp = ft_strjoin(*str_temp, temp);
		if (*str_temp && *str_temp[0] == '\0')
			*str_temp = NULL;
	}
	return (free(temp), 0);
}

static void	init_var(char **str_temp, int *i, t_vars *vars)
{
	vars->catsh = *i;
	vars->befor_sing = *i;
	*str_temp = ft_strdup("");
	if (!str_temp)
		return ;
}

int	ft_arealpha(t_vars *vars, int *i, t_list **comm, t_env **envir)
{
	char	*str_temp;
	t_args	args;

	init_var(&str_temp, i, vars);
	args.vars = vars;
	args.i = i;
	args.str_temp = &str_temp;
	while (vars->read[*i])
	{
		if (!ft_issep(vars->read[*i]) && !ft_isspace(vars->read[*i])
			&& !ft_isquotes(vars->read[*i]) && vars->read[*i] != '$')
			add_to_temp(&str_temp, i, vars->read);
		else
		{
			if (vars->read[*i] == '$')
			{
				return (handle_dollar(&args, envir, comm), 0);
			}
			else
				break ;
		}
	}
	return (free(str_temp), returning(vars, i, comm));
}
