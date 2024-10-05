/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:50:06 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/09 23:39:20 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_numeric_arg(char *arg, t_vars *vars)
{
	ft_put_error("minishell: exit: ", arg, ": numeric argument required");
	vars->exit_status = 255;
	return (0);
}

int	ft_too_many_args(t_vars *vars)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	vars->exit_status = 1;
	return (0);
}

int	ft_isvalid_arg(char *arg, t_vars *vars)
{
	int	i;
	int	stat;

	i = 0;
	if (arg && (arg[i] == '-' || arg[i] == '+'))
		i++;
	while (arg && ft_isdigit(arg[i]))
		i++;
	while (arg && ft_isspace(arg[i]))
		i++;
	if (arg && arg[i])
		return (ft_numeric_arg(arg, vars));
	if(isLongmin(arg))
	{
		vars->exit_status = 0;
		return (1);
	}
	stat = ft_atoi_2(arg, vars);
	if (vars->atoifail)
		return (ft_numeric_arg(arg, vars));
	vars->exit_status = stat;
	return (1);
}

int	ft_exit_error(t_list *comm, t_vars *vars)
{
	t_list	*temp;

	temp = comm;
	if (!comm || !(*comm->content))
		return (-1);
	if (!ft_isvalid_arg(comm->content, vars))
		return (-1);
	comm = comm->next;
	if (comm && comm->content)
		return (ft_too_many_args(vars), -2);
	return (0);
}

int	ft_exit(t_list *comm, t_vars *vars)
{
	if (!comm)
		return (-1);
	comm = comm->next;
	if (!comm)
	{
		ft_putstr_fd("exit\n",2);
		exit(vars->exit_status);
	}
	if (!(*comm->content))
	{
		ft_numeric_arg(comm->content, vars);
		exit(vars->exit_status);
	}
	if (ft_exit_error(comm, vars) == -2)
		return (-1);
	if (!vars->numofpipes)
	{
		ft_putstr_fd("exit\n",2);
		exit(vars->exit_status);
	}
	return (0);
}
