/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 03:36:11 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/28 14:05:41 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_env *envir, t_vars *vars)
{
	t_env	*temp;

	temp = envir;
	while (temp)
	{
		vars->exit_status = 0;
		if (temp->value
			&& ft_strncmp(temp->key, "PATH\0", 5) == 0 && vars->env_i == 1)
			temp = temp->next;
		if (temp->value && ft_strncmp(temp->key, "2PWD\0", 5) != 0
			&& ft_strncmp(temp->key, "1_\0", 3) != 0)
		{
			ft_putstr_fd(temp->key, vars->pfd[1]);
			ft_putchar_fd('=', vars->pfd[1]);
			ft_putstr_fd(temp->value, vars->pfd[1]);
			ft_putchar_fd('\n', vars->pfd[1]);
		}
		temp = temp->next;
	}
}
