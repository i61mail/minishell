/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:39:39 by mait-lah          #+#    #+#             */
/*   Updated: 2024/08/27 05:58:12 by mait-lah         ###   ########.fr       */
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

int	ft_echo(t_list *command)
{
	int		is_n;

	is_n = 1;
	command = command->next;
	while (command && ft_isflag(command->content))
	{
		is_n = 0;
		command = command->next;
	}
	while (command)
	{
		printf("%s", command->content);
		if (command->next)
			printf(" ");
		command = command->next;
	}
	if (is_n)
		printf("\n");
	return (0);
}
