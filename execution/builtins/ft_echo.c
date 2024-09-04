/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:39:39 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/04 11:59:28 by isrkik           ###   ########.fr       */
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
	t_list *temp;
	t_list *temp1;

	is_n = 1;
	temp = command;
	temp1 = command;
	while (temp && temp->type != PIP)
		temp = temp->next;
	if (temp && temp->type == PIP)
	{
		ft_run(vars, command, envir);
		return (0);
	}
	command = command->next;
	while (command && ft_isflag(command->content))
	{
		is_n = 0;
		command = command->next;
	}
	if (vars->not_red == 0 || (vars->not_enter == 1 && vars->red_built == 1))
	{
		dup2(1, vars->fd_buil);
	}
	else if (vars->red_built == 1 && vars->pipe > 0)
	{
		dup2(vars->pfd[1], vars->fd_buil);
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
		ft_putstr_fd(command->content, vars->fd_buil);
		if (command->next)
			ft_putstr_fd(" ", vars->fd_buil);
		command = command->next;
	}
	if (is_n)
	{
		ft_putstr_fd("\n", vars->fd_buil);
	}
	return (0);
}
