/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 03:36:11 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/01 11:00:07 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_env *envir, t_vars *vars, t_list *command)
{
	t_env *temp;

	temp = envir;
	while (temp)
	{
		while (command && command->type != PIP)
			command = command->next;
		if (command && command->type == PIP)
		{
			ft_run(vars, command, envir);
			return ;
		}
		if (temp->value && ft_strcmp(temp->key,"OLDPWD\0"))
		{
			ft_putstr_fd(temp->key, vars->pfd[1]);
			ft_putchar_fd('=', vars->pfd[1]);
			ft_putstr_fd(temp->value, vars->pfd[1]);
			ft_putchar_fd('\n', vars->pfd[1]);
		}
		temp = temp->next;
	}
}
