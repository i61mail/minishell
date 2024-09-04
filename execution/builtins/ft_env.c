/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 03:36:11 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/04 11:54:28 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_env *envir, t_vars *vars, t_list *command)
{
	t_env *temp;
	t_list *temp1;

	temp = envir;
	temp1 = command;
	while (temp)
	{
		while (command && command->type != PIP)
			command = command->next;
		if (command && command->type == PIP)
		{
			ft_run(vars, temp1, envir);
			return ;
		}
		if (vars->not_red == 0 || (vars->not_enter == 1 && vars->red_built == 1))
		{
			dup2(1, vars->fd_buil);
		}
		else if (vars->red_built == 1 && vars->numofpipes > 0)
		{
			dup2(vars->pfd[1], vars->fd_buil);
		}
		if (temp->value && ft_strcmp(temp->key,"OLDPWD\0"))
		{
			ft_putstr_fd(temp->key, vars->fd_buil);
			ft_putchar_fd('=', vars->fd_buil);
			ft_putstr_fd(temp->value, vars->fd_buil);
			ft_putchar_fd('\n', vars->fd_buil);
		}
		temp = temp->next;
	}
}
