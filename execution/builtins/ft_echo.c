/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:39:39 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/27 17:18:30 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_isflag(char *str)
{
	if (!str || !(*str) || *str != '-')
		return (0);
	str++;
	if (!(*str))
		return (0);
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

int	ft_echo(t_list *command, t_vars *vars)
{
	int		is_n;

	is_n = 1;
	command = command->next;
	while (command && ft_isflag(command->content))
	{
		is_n = 0;
		command = command->next;
	}
	while (command && !ft_isred(command->type))
	{
		if (command->type == HEREDOC)
			command = command->next;
		else
		{
			ft_putstr_fd(command->content, vars->pfd[1]);
			if (command->next)
				ft_putstr_fd(" ", vars->pfd[1]);
		}
		command = command->next;
	}
	if (is_n)
		ft_putstr_fd("\n", vars->pfd[1]);
	return (vars->exit_status = 0);
}
