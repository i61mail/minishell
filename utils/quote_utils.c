/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 09:02:03 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/10 15:40:07 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_dollar(char *str, int *i)
{
	int	k;

	k = 0;
	(*i)--;
	while (str[*i] == '$')
	{
		(*i)++;
		k++;
	}
	if (k % 2 == 0)
		return (k);
	else
		return (k - 1);
	return (0);
}

int	quotes(t_vars *vars, int *i, t_list **comm, t_env **envir)
{
	if (ft_isquotes(vars->read[*i]))
	{
		if (even_odd(vars->read) == 0)
		{
			ft_error(comm);
			return (-1);
		}
		ft_arequotes(vars, i, comm, envir);
	}
	return (0);
}
