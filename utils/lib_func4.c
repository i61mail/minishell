/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_func4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 10:48:32 by isrkik            #+#    #+#             */
/*   Updated: 2024/08/11 10:49:23 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check(unsigned long long result, int i, char *str, int sign)
{
	if (sign == -1 && result == 9223372036854775808ULL)
	{
		if (ft_isdigit(str[i]) == 1)
			return (-1);
		return (1);
	}
	if (result > LLONG_MAX)
		return (-1);
	return (0);
}

long long	ft_atoi(char *str)
{
	unsigned long long	result;
	int					i;
	int					sign;

	result = 0;
	i = 0;
	sign = 1;
	if (!str)
		return (-1);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + str[i++] - 48;
		if (ft_check(result, i, str, sign) == -1)
			return (-1);
		else if (ft_check(result, i, str, sign) == 1)
			return (result * sign);
	}
	return (result * sign);
}
