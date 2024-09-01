/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:28:00 by mait-lah          #+#    #+#             */
/*   Updated: 2024/08/31 18:43:04 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_vars *vars, t_env *envir)
{
	char	*pwd;
	(void)envir;
	pwd = NULL;
	pwd = getcwd(pwd, PATH_MAX);
	if (!pwd)
		return (perror("getcwd"), errno);
	write(vars->pfd[1], pwd, ft_strlen(pwd));
	ft_putchar_fd('\n', vars->pfd[1]);
	return (0);
}
