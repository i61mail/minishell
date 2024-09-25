/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:17:22 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/25 12:20:38 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_file_err(char *binary, t_vars *vars)
{
	struct stat	path;

	stat(binary, &path);
	if (S_ISDIR(path.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(binary, 2);
		ft_putstr_fd(": is a directory\n", 2);
		return (vars->exit_status = 126);
	}
	if (S_ISREG(path.st_mode) && access(binary, X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(binary, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (vars->exit_status = 126);
	}
	if (access(binary, F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(binary, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (vars->exit_status = 127);
	}
	return (0);
}
