/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:17:22 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/29 16:16:58 by isrkik           ###   ########.fr       */
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

int	ft_put_error(char *before, char *sep, char *after)
{
	ft_putstr_fd(before, 2);
	ft_putstr_fd(sep, 2);
	ft_putstr_fd(after, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	ft_is_builtin(char *command)
{
	if (!ft_strcmp(command, "cd\0") || !ft_strcmp(command, "echo\0")
		|| !ft_strcmp(command, "env\0")
		|| !ft_strcmp(command, "exit\0") || !ft_strcmp(command, "export\0")
		|| !ft_strcmp(command, "pwd\0") || !ft_strcmp(command, "unset\0"))
		return (1);
	return (0);
}
