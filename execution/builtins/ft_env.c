/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: i61mail <i61mail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 03:36:11 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/19 21:09:08 by i61mail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_env *envir, t_vars *vars)
{
	t_env	*temp;

	temp = envir;
	while (temp)
	{
		if (temp->value && ft_strncmp(temp->key, "PATH\0", 5) == 0 && vars->env_i == 1)
			temp = temp->next;
		if (temp->value && ft_strncmp(temp->key, "2PWD\0", 5) != 0)
		{
			ft_putstr_fd(temp->key, vars->pfd[1]);
			ft_putchar_fd('=', vars->pfd[1]);
			ft_putstr_fd(temp->value, vars->pfd[1]);
			ft_putchar_fd('\n', vars->pfd[1]);
		}
		temp = temp->next;
	}
}
