/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:39:39 by mait-lah          #+#    #+#             */
/*   Updated: 2024/08/22 16:09:37 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_isflag(char *str)
{
	if (!str || !(*str) || *str != '-')
		return (0);
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

int	ft_echo(char *command)
{
	int		is_n;
	int		i;
	char **_2dcommand;

	is_n = 1;
	i = 1;
	_2dcommand = ft_split(command,' ');
	while (_2dcommand[i] && ft_isflag(_2dcommand[i]))
	{
		is_n = 0;
		i++;
	}
	while (_2dcommand[i])
	{
		printf("%s", _2dcommand[i]);
		if (_2dcommand[i + 1])
			printf(" ");
		i++;
	}
	if (is_n)
		printf("\n");
	return (0);
}
