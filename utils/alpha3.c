/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:56:11 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/27 10:25:46 by isrkik           ###   ########.fr       */
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
	if (args->vars->bef_dollar == 0 && args->vars->not_pass == 1)
		free(*(args->str_temp));
	if (sspace(*(args->str_temp)) == 0 && args->vars->check_ambiguous == 1)
		type = AMBIGUOUS;
	if (args->vars->not_pass == 0 || *(args->str_temp)[0] != '\0')
	{
		replace_expand(*(args->str_temp), comm, type);
	}
	return (0);
}
