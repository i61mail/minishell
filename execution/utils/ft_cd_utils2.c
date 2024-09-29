/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:13:09 by isrkik            #+#    #+#             */
/*   Updated: 2024/09/29 16:15:05 by isrkik           ###   ########.fr       */
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
