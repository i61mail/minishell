/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:50:06 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/01 11:38:30 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit(t_vars *vars, t_env **envir, t_list *comm)
{
	int	id;

	while (comm && comm->type != PIP)
		comm = comm->next;
	if (comm && comm->type == PIP)
	{
		ft_run(vars, comm, *envir);
		return (0);
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
