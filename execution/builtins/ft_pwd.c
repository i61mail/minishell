/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:28:00 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/05 15:40:26 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_my_pwd(t_env **envir, char **save_pwd)
{
	t_env *temp;

	temp = *envir;
	while (temp)
	{
		if (ft_strcmp(temp->key, "_PWD") == 0)
			*save_pwd = ft_strdup(temp->value);
		temp = temp->next;
	}
	return (0);
}

int	ft_pwd(t_vars *vars, t_env **envir)
{
	static char	*save_pwd;
	char	*pwd;
	pwd = NULL;
	pwd = getcwd(pwd, PATH_MAX);
	if (!pwd)
	{
		get_my_pwd(envir, &save_pwd);
		pwd = save_pwd;
	}
	save_pwd = pwd;
	write(vars->pfd[1], pwd, ft_strlen(pwd));
	ft_putchar_fd('\n', vars->pfd[1]);
	return (0);
}

