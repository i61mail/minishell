/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:50:06 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/04 11:54:15 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit(t_vars *vars, t_env **envir, t_list *comm)
{
	int	id;
	t_list *temp;

	temp = comm;
	while (comm && comm->type != PIP)
		comm = comm->next;
	if (comm && comm->type == PIP)
	{
		ft_run(vars, temp, *envir);
		return (0);
	}
	if (vars->not_red == 0 || (vars->not_enter == 1 && vars->red_built == 1))
	{
		dup2(1, vars->fd_buil);
	}
	else if (vars->red_built == 1 && vars->numofpipes > 0)
	{
		dup2(vars->pfd[1], vars->fd_buil);
	}
	if (vars->numofpipes)
	{
		id = fork();
		if (!id)
			exit(vars->exit_status);
		else
			wait(NULL);
	}
	else
	{
		ft_putstr_fd("exit\n",vars->pfd[1]);
		exit(vars->exit_status);
	}
	return (0);
}
