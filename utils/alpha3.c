/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:56:11 by isrkik            #+#    #+#             */
/*   Updated: 2024/10/01 13:27:58 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_space(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (ft_isspace(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	double_pointer(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	returning(t_vars *vars, int *i, t_list **comm)
{
	if (vars->read[*i] && ft_isquotes(vars->read[*i]))
		return (2);
	if (ft_token(vars, *i, comm, COMM) == -1)
		return (-1);
	return (0);
}

int	handle_dollar(t_args *args, t_env **envir, t_list **comm)
{
	int	hold;
	int	type;

	type = 0;
	args->vars->not_pass = 0;
	check_splited(args->vars, args->i, &type);
	hold = ft_dollar(args->vars, args->i, args->str_temp, envir);
	if (hold == 2)
		return (split_before_quotes(args->vars, args->str_temp, comm, args->i),
			free(*(args->str_temp)), 2);
	if (sspace(*(args->str_temp)) == 0 && args->vars->check_ambiguous == 1)
		type = AMBIGUOUS;
	if (args->vars->not_pass == 0 || *(args->str_temp)[0] != '\0')
	{
		replace_expand(*(args->str_temp), comm, type);
		return (0);
	}
	if (args->vars->bef_dollar == 0 && args->vars->not_pass == 1)
	{
		free(*(args->str_temp)); // double free
	}
	return (0);
}

char	*check_last_arg(t_vars *vars, char **exp, char **comp)
{
	if (vars->numofpipes > 0 && vars->last_arg)
	{
		free(vars->last_arg);
		vars->last_arg = NULL;
		return (free(*comp), *exp);
	}
	if (vars->last_arg)
	{
		free(*exp);
		*exp = ft_strdup(vars->last_arg);
		return (free(*comp), *exp);
	}
	return (free(*comp), free(*exp), NULL);
}
