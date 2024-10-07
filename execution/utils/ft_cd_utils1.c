/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:05:27 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/30 17:49:53 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cd_error(void)
{
	ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
	ft_putstr_fd("cannot access parent directories: ", 2);
	ft_putstr_fd("No such file or directory\n", 2);
}

void	reg_dir(char **old_pwd, t_env **envir)
{
	if (*old_pwd)
		free(*old_pwd);
	*old_pwd = update_old_pwd(envir);
	update_pwd(envir, 0, old_pwd);
}

void	ft_remove_dir(char **old_pwd, t_env **envir, t_list *comm)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (cwd == NULL)
	{
		if (ft_strncmp(comm->content, "..\0", 3) == 0)
		{
			free(*old_pwd);
			*old_pwd = update_old_pwd(envir);
			update_pwd(envir, 2, old_pwd);
			cd_error();
		}
		else if (ft_strncmp(comm->content, ".\0", 2) == 0)
		{
			free(*old_pwd);
			*old_pwd = update_old_pwd(envir);
			update_pwd(envir, 3, old_pwd);
			cd_error();
		}
	}
	else
		reg_dir(old_pwd, envir);
	free(cwd);
}

void	check_permission(t_vars *vars, t_list *comm)
{
	struct stat	path_stat;

	if (access(comm->content, F_OK) == -1)
	{
		ft_put_error_cd2(vars, comm);
		return ;
	}
	else if (stat(comm->content, &path_stat) == -1)
	{
		ft_put_error_cd("minishell: cd:", comm->content, ": stat error", vars);
		return ;
	}
	else if (S_ISDIR(path_stat.st_mode))
	{
		if (access(comm->content, X_OK) == -1)
		{
			ft_put_error_cd("minishell: cd:", comm->content,
				": Permission denied", vars);
		}
		else if (vars->numofpipes == 0)
			ft_put_error_cd2(vars, comm);
	}
	else
		ft_put_error_cd("minishell: cd:", comm->content,
			": Not a directory", vars);
}

void	update_pwd2(t_env *env, char **pwd, char *points)
{
	while (env)
	{
		if (ft_strncmp(env->key, "2PWD\0", 5) == 0)
		{
			free(env->value);
			env->value = ft_strdup(*pwd);
			env->value = ft_strjoin(env->value, points);
		}
		else if (ft_strncmp(env->key, "PWD\0", 4) == 0)
		{
			free(env->value);
			env->value = ft_strdup(*pwd);
			env->value = ft_strjoin(env->value, points);
			free(*pwd);
			*pwd = ft_strdup(env->value);
		}
		env = env->next;
	}
}
