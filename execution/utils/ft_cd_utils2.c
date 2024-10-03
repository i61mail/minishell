/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: i61mail <i61mail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:13:09 by isrkik            #+#    #+#             */
/*   Updated: 2024/10/01 22:30:18 by i61mail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	up_oldpwd_util(t_env *env, char *pwd)
{
	if (ft_strncmp(env->key, "OLDPWD\0", 7) == 0)
	{
		free(env->value);
		env->value = ft_strdup(pwd);
	}
}

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
		up_oldpwd_util(env, pwd);
		env = env->next;
	}
	return (pwd);
}

void	check_env(t_env **envir, char **old_pwd)
{
	t_env	*temp;

	temp = *envir;
	while (temp)
	{
		if (ft_strncmp(temp->key, "OLDPWD\0", 7) == 0)
		{
			if (temp->value)
			{
				free(*old_pwd);
				*old_pwd = ft_strdup(temp->value);
			}
			return ;
		}
		temp = temp->next;
	}
	if (!temp)
	{
		free(*old_pwd);
		*old_pwd = NULL;
	}
}

void	up_pwd_util(t_env *env, char **str, int *flag)
{
	if (ft_strncmp(env->key, "2PWD\0", 5) == 0)
	{
		free(env->value);
		*str = getcwd(NULL, 0);
		env->value = ft_strdup(*str);
		free(*str);
	}
	else if (ft_strncmp(env->key, "PWD\0", 4) == 0)
	{
		*flag = 1;
		free(env->value);
		*str = getcwd(NULL, 0);
		env->value = ft_strdup(*str);
		free(*str);
	}
}
