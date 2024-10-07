/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: i61mail <i61mail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:39:54 by isrkik            #+#    #+#             */
/*   Updated: 2024/10/01 22:29:03 by i61mail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	init_vars(int *flag, char **str, char **points)
{
	*flag = 0;
	*str = NULL;
	*points = NULL;
}

void	up_pwd_util2(t_env *env, char **str, int *flag, t_env **envir)
{
	char	*cwd;

	cwd = NULL;
	while (env)
	{
		up_pwd_util(env, str, flag);
		env = env->next;
	}
	if (*flag == 0)
	{
		cwd = getcwd(NULL, 0);
		add_to_node(ft_strdup("PWD"), ft_strdup(cwd), envir);
		free(cwd);
	}
}

int	update_pwd(t_env **envir, int bool, char **pwd)
{
	t_env		*env;
	char		*points;
	char		*str;
	int			flag;

	init_vars(&flag, &str, &points);
	env = *envir;
	if (bool == 0)
		up_pwd_util2(env, &str, &flag, envir);
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

void	to_oldpwd(t_list *comm, char **old_pwd, t_vars *vars, t_env **envir)
{
	int	var_chdir;

	check_env(envir, old_pwd);
	var_chdir = 0;
	if (vars->numofpipes == 0)
		var_chdir = chdir(*old_pwd);
	if (var_chdir == 0)
	{
		ft_putstr_fd(*old_pwd, 1);
		ft_putstr_fd("\n", 1);
	}
	else if (var_chdir == -1)
	{
		vars->old_pwd = 1;
		ft_put_error("minishell: ", comm->content, ": OLDPWD not set");
		vars->exit_status = 1;
	}
}

void	to_home(t_vars *vars, t_env *envir)
{
	if (!vars->numofpipes && chdir(my_getenv("HOME", envir)))
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		vars->exit_status = 1;
	}
}
