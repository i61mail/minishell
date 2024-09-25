/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:04:55 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/25 17:29:28 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	even_odd2(char *read, int *check, int sing, int i)
{
	if (read[i] == 34 && sing == 0)
	{
		if (*check >= 1)
			*check = 0;
		else
			*check += 1;
	}
	return (0);
}

int	even_odd(char *read)
{
	int	i;
	int	check;
	int	sing;

	sing = 0;
	check = 0;
	i = 0;
	while (read[i])
	{
		even_odd2(read, &check, sing, i);
		if (read[i] == 39 && check == 0)
		{
			if (sing >= 1)
				sing = 0;
			else
				sing += 1;
		}
		i++;
	}
	if (check % 2 == 0 && sing % 2 == 0)
		return (1);
	return (0);
}

void	skip_digit(t_vars *vars, int *i, int *check)
{
	if (ft_isdigit(vars->read[*i]))
	{
		*check = 1;
		(*i)++;
	}
}

int	sspace(char *str_temp)
{
	int	i;

	i = 0;
	while (str_temp[i])
	{
		if (ft_isspace(str_temp[i]))
			return (0);
		i++;
	}
	return (1);
}
