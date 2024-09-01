/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 03:36:11 by mait-lah          #+#    #+#             */
/*   Updated: 2024/08/31 18:35:00 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_env *envir, t_vars *vars)
{
	t_env *temp;

	temp = envir;
	while (temp)
	{
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
