/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:05:03 by isrkik            #+#    #+#             */
/*   Updated: 2024/10/07 13:29:17 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	up_oldpwd_util(t_env *env, char *pwd, int *flag)
{
	if (ft_strncmp(env->key, "OLDPWD\0", 7) == 0)
	{
		*flag = 1;
		free(env->value);
		env->value = ft_strdup(pwd);
	}
}

void	up_oldpwd_util2(t_env *env, char *pwd, t_env **envir)
{
	int	flag;

	flag = 0;
	while (env)
	{
		up_oldpwd_util(env, pwd, &flag);
		env = env->next;
	}
	if (flag == 0)
		add_to_node("OLDPWD", ft_strdup(pwd), envir);
}

void	ft_put_error_cd2(t_vars *vars, t_list *comm)
{
	ft_put_error_cd("minishell: cd:", comm->content,
		": No such file or directory", vars);
}
