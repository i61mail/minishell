/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:50:06 by mait-lah          #+#    #+#             */
/*   Updated: 2024/08/31 18:39:41 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit(t_vars *vars)
{
	int	id;

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
