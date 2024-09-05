/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:50:06 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/05 17:57:29 by isrkik           ###   ########.fr       */
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
int		 ft_exit_err(t_list *comm,t_vars *vars)
{
	long long status;

	status = 0;
	if (!comm)
		return (0);
	if (!ft_isalldegit(comm->content))
	{
		ft_putstr_fd("exit\nminishell: exit: numeric argument required\n", 2);
		vars->exit_status = 1;
		return (-1);
	}
	status = ft_atoi(comm->content);
	if(status == -1)
	{
		ft_putstr_fd("exit\nminishell: exit: numeric argument required\n", 2);
		vars->exit_status = 255;
		return (-1);
	}
	if (comm->next)
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		vars->exit_status = 1;
		return (1);
	}
	return (status);
}
int	ft_exit(t_list *comm, t_vars *vars)
{
	int	id;
	int	status;

	id = 0;
	if (!comm)
		return (-1);
	comm = comm->next;
	status  = ft_exit_err(comm, vars);
	if(status == 1)
		return (-1);
	if (vars->numofpipes)
	{
		id = fork();
		if (!id)
			exit(status);
		else
			wait(NULL);
		return (0);
	}
	else
	{
		// if(!status) // ana li 7ydtha hit la exiti b chi haja mn ghir 0 makatprintach exit
		ft_putstr_fd("exit\n",vars->pfd[1]);
		exit(status);
	}
	return (0);
}
