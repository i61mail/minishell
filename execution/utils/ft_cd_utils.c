/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:39:54 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/29 11:02:37 by isrkik           ###   ########.fr       */
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
		if (ft_strncmp(env1->key, "2PWD\0", 5) == 0
			|| ft_strncmp(env1->key, "PWD\0", 4) == 0)
		{
			free(pwd);
			pwd = ft_strdup(env1->value);
			if (!pwd)
				return (NULL);
		}
		env1 = env1->next;
	}
	while (env)
	{
		if (ft_strncmp(env->key, "OLDPWD\0", 7) == 0)
		{
			free(env->value);
			env->value = ft_strdup(pwd);
		}
		env = env->next;
	}
	return (pwd);
}

void	update_pwd2(t_env *env, char **pwd, char *points)
{
	while (env)
	{
		if (ft_strncmp(env->key, "2PWD\0", 5) == 0)
		{
			env->value = ft_strdup(*pwd);
			env->value = ft_strjoin(env->value, points);
		}
		else if (ft_strncmp(env->key, "PWD\0", 4) == 0)
		{
			env->value = ft_strdup(*pwd);
			env->value = ft_strjoin(env->value, points);
			*pwd = ft_strdup(env->value);
		}
		env = env->next;
	}
}

int	update_pwd(t_env **envir, int bool, char **pwd)
{
	t_env		*env;
	char		*points;
	char		*str;

	str = NULL;
	points = NULL;
	env = *envir;
	if (bool == 0)
	{
		while (env)
		{
			if (ft_strncmp(env->key, "2PWD\0", 5) == 0)
			{
				free(env->value);
				str = getcwd(NULL, 0);
				env->value = ft_strdup(str);
				free(str);
			}
			else if (ft_strncmp(env->key, "PWD\0", 4) == 0)
			{
				free(env->value);
				str = getcwd(NULL, 0);
				env->value = ft_strdup(str);
				free(str);
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
		update_pwd2(env, pwd, points);
	}
	return (0);
}

void	to_oldpwd(t_list *comm, char **old_pwd, t_vars *vars, int *first_time)
{
	int	var_chdir;

	var_chdir = chdir(*old_pwd);
	if (var_chdir == 0)
	{
		ft_putstr_fd(*old_pwd, 1);
		ft_putstr_fd("\n", 1);
	}
	else if (var_chdir == -1)
	{
		*first_time = 1;
		ft_put_error("minishell: ", comm->content, ": OLDPWD not set");
		vars->exit_status = 1;
	}
}

void	to_home(t_vars *vars)
{
	if (chdir(getenv("HOME")))
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		vars->exit_status = 1;
	}
}
