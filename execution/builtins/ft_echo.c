/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:39:39 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/01 12:03:27 by isrkik           ###   ########.fr       */
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

int	ft_echo(t_list *command, t_vars *vars, t_env *envir)
{
	int		is_n;
	int		check;

	check = 0;
	is_n = 1;
	command = command->next;
	while (command && ft_isflag(command->content))
	{
		is_n = 0;
		command = command->next;
	}
	while (command && !ft_isred(command->type) && command->type != PIP)
	{
		if (command->type == HEREDOC)
		{
			command = command->next;
			if(command->next)
				command = command->next;
			continue;
		}
		ft_putstr_fd(command->content, vars->pfd[1]);
		if (command->next)
			ft_putstr_fd(" ", vars->pfd[1]);
		command = command->next;
	}
	if (command && ft_isred(command->type) && command->type != PIP)
	{
		check = 1; 	
		command = ft_check4red(command, vars);
	}
	if (command && command->type == PIP)
	{
		ft_run(vars, command, envir);
		return (0);
	}
	if (is_n && check == 0)
	{
		ft_putstr_fd("\n", vars->pfd[1]);
	}
	return (0);
}
