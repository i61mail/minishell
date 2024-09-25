/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:34:46 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/25 12:21:00 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*update_old_pwd(t_env **envir)
{
	t_env		*env;
	t_env		*env1;
	char		*pwd;

	pwd = NULL;
	env = *envir;
	env1 = *envir;
	while (env1)
	{
		if (ft_strncmp(env1->key, "2PWD\0", 5) == 0)
		{
			pwd = ft_strdup(env1->value);
			if (!pwd)
				return (NULL);
		}
		else if (ft_strncmp(env1->key, "PWD\0", 4) == 0)
		{
			pwd = ft_strdup(env1->value);
			if (!pwd)
				return (NULL);
		}
		env1 = env1->next;
	}
	while (env)
	{
		if (ft_strcmp(env->key, "OLDPWD") == 0)
			env->value = ft_strdup(pwd);
		env = env->next;
	}
	return (pwd);
}

int	update_pwd(t_env **envir, int bool, char **pwd)
{
	t_env		*env;
	char		*points;

	points = NULL;
	env = *envir;
	if (bool == 0)
	{
		while (env)
		{
			if (ft_strcmp(env->key, "2PWD") == 0)
			{
				env->value = ft_strdup(getcwd(NULL, 0));
			}
			else if (ft_strcmp(env->key, "PWD") == 0)
			{
				env->value = ft_strdup(getcwd(NULL, 0));
			}
			env = env->next;
		}
	}
	else if (bool == 2 || bool == 3)
	{
		if (bool == 2)
			points = "/..";
		else
			points = "/.";
		while (env)
		{
			if (ft_strcmp(env->key, "2PWD") == 0)
			{
				env->value = ft_strdup(*pwd);
				env->value = ft_strjoin(env->value, points);
			}
			else if (ft_strcmp(env->key, "PWD") == 0)
			{
				env->value = ft_strdup(*pwd);
				env->value = ft_strjoin(env->value, points);
				*pwd = ft_strdup(env->value);
			}
			env = env->next;
		}
	}
	return (0);
}

int	ft_cd(t_vars *vars, t_list *comm, t_env **envir)
{
	char		*cwd;
	static char	*old_pwd;
	int			var_chdir;

	cwd = NULL;
	var_chdir = 0;
	if (vars->numofpipes)
		return (0);
	if (comm && comm->next)
	{
		comm = comm->next;
		if (ft_strncmp(comm->content, "-\0", 2) == 0)
		{
			var_chdir = chdir(old_pwd);
			if (var_chdir == 0)
			{
				ft_putstr_fd(old_pwd, 1);
				ft_putstr_fd("\n", 1);
			}
			else if (var_chdir == -1)
			{
				ft_put_error("minishell: ", comm->content, ": OLDPWD not set");
				vars->exit_status = 1;
			}
		}
		else if (ft_strncmp(comm->content, "~\0", 2) == 0)
		{
			if (chdir(getenv("HOME")))
			{
				ft_putstr_fd("minishell: cd: HOME not set\n", 2);
				vars->exit_status = 1;
			}
		}
		else
		{
			if (*comm->content == '\0')
			{
				old_pwd = update_old_pwd(envir);
				update_pwd(envir, 0, &old_pwd);
				return (0);
			}
			var_chdir = chdir(comm->content);
			if (var_chdir != -1)
			{
				cwd = getcwd(cwd, 0);
				if (cwd == NULL)
				{
					if (ft_strncmp(comm->content, "..\0", 3) == 0)
					{
						old_pwd = update_old_pwd(envir);
						update_pwd(envir, 2, &old_pwd);
						ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
					}
					else if (ft_strncmp(comm->content, ".\0", 2) == 0)
					{
						old_pwd = update_old_pwd(envir);
						update_pwd(envir, 3, &old_pwd);
						ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
					}
				}
				else
				{
					old_pwd = update_old_pwd(envir);
					update_pwd(envir, 0, &old_pwd);
				}
			}
			else
			{
				vars->exit_status = 1;
				if (access(comm->content, F_OK) == -1)
					ft_put_error("minishell: cd:", comm->content, ": No such file or directory");
				else
					ft_put_error("minishell: cd: ", comm->content, ": permission denied");
			}
		}
	}
	else if (comm && !comm->next)
	{
		if (chdir(getenv("HOME")))
		{
			vars->exit_status = 1;
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		}
	}
	return (0);
}
