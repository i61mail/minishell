/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:34:46 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/05 17:40:52 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*update_old_pwd(t_env **envir)
{
	t_env 		*env;
	t_env 		*env1;
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

int	update_pwd(t_env **envir, int bool, char *pwd)
{
	t_env 		*env;

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
	else if (bool == 2)
	{
		while (env)
		{
			if (ft_strcmp(env->key, "2PWD") == 0)
			{
				env->value = ft_strdup(pwd);
				env->value = ft_strjoin(env->value, "/..");
			}
			else if (ft_strcmp(env->key, "PWD") == 0)
			{
				env->value = ft_strdup(pwd);
				env->value = ft_strjoin(env->value, "/..");
				pwd = ft_strdup(env->value);
			}
			env = env->next;
		}
	}
	return (0);
}

int	ft_cd(t_vars *vars, t_list *comm, t_env **envir)
{
	char	*cwd;
	static char *old_pwd;
	int		var_chdir = 0;

	cwd = NULL;
	if(vars->numofpipes)
		return (0);
	if (comm && comm->next)
	{
		comm = comm->next;
		if (ft_strncmp(comm->content, "-\0", 2) == 0)
		{
			var_chdir  = chdir(old_pwd);
			if (var_chdir == 0)
				printf("%s\n", old_pwd);
			else if (var_chdir == -1)
			{
				vars->exit_status = 1;
				printf("bash: %s: OLDPWD not set\n", comm->content);
			}
			
		}
		else if (ft_strncmp(comm->content, "~\0", 2) == 0)
		{
			if (chdir("/Users/isrkik"))
			{
				vars->exit_status = 1;
				printf("minishell: cd: %s: No such file or directory\n", comm->content);
			}
		}
		else
		{
			var_chdir = chdir(comm->content);
			if (var_chdir != -1)
			{
				cwd = getcwd(cwd, 0);
				if (cwd == NULL)
				{
					if (ft_strncmp(comm->content, "..\0", 3) == 0)
					{
						update_pwd(envir, 2, old_pwd);
						printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
					}
				}
				else
					update_pwd(envir, 0, old_pwd);
			}
			else
			{
				vars->exit_status = 1;
				printf("minishell: cd: %s: No such file or directory\n", comm->content);
			}
		}
	}
	else if (comm && !comm->next)
	{
		if (chdir("/Users/isrkik"))
		{
			vars->exit_status = 1;
			printf("minishell: cd: %s: No such file or directory\n", comm->content);
		}
	}
	if (var_chdir != -1)
		old_pwd = update_old_pwd(envir);
	return (0);
}
