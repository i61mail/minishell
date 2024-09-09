/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:50:06 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/09 06:23:42 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_isalldegit(char *str)
{
	while (str && *str)
	{
		if (!ft_isdigit(*str) && *str != '"' && *str != '+' && *str != '-')
			return (0);
		str++;
	}
	return (1);
}

int	ft_exit_err(t_list *comm, t_vars *vars)
{
	unsigned int	status;

	vars->atoifail = 0;
	status = 0;
	if (!comm)
		return (0);
	status = ft_atoi_2(comm->content, vars);
	if (vars->atoifail)
	{
		ft_put_error("exit\nminishell: exit: ",
			comm->content, ": numeric argument required");
		vars->atoifail = 1;
		exit(vars->exit_status = 255);
		return (-1);
	}
	if (comm->next)
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		vars->exit_status = 1;
		vars->atoifail = 1;
		return (1);
	}
	return (status);
}

int	ft_exit(t_list *comm, t_vars *vars)
{
	int	id;
	int	status;

	id = 0;
	comm = comm->next;
	status = ft_exit_err(comm, vars);
	if (vars->atoifail)
		return (-1);
	if (vars->numofpipes)
	{
		if (!vars->pipe)
			vars->exit_status = ft_atoi_2(comm->content, vars);
		id = fork();
		if (!id)
			exit(status);
		else
			wait(NULL);
		return (0);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		exit(status);
	}
	return (0);
}
