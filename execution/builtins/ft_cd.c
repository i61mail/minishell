/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: i61mail <i61mail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:34:46 by mait-lah          #+#    #+#             */
/*   Updated: 2024/10/01 21:12:11 by i61mail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cd_noargs(t_env **envir, t_vars *vars)
{
	if (!vars->numofpipes && chdir(my_getenv("HOME", *envir)))
	{
		vars->exit_status = 1;
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	}
}

void	regul_dir(t_vars *vars, char **old_pwd, t_list *comm, t_env **envir)
{
	int	i;

	i = 0;
	if (*comm->content == '\0')
	{
		free(*old_pwd);
		*old_pwd = update_old_pwd(envir);
		update_pwd(envir, 0, old_pwd);
		return ;
	}
	if (vars->numofpipes == 0)
	{
		i = chdir(comm->content);
		if (!vars->numofpipes && i != -1)
			ft_remove_dir(old_pwd, envir, comm);
		else
			check_permission(vars, comm);
	}
	else if (vars->numofpipes != 0)
		check_permission(vars, comm);
}

void	cd_oldpwd(t_list *comm, t_vars *vars, char **old_pwd, t_env **envir)
{
	to_oldpwd(comm, old_pwd, vars, envir);
	if (vars->old_pwd == 1)
	{
		vars->old_pwd = 0;
		return ;
	}
	free(*old_pwd);
	*old_pwd = update_old_pwd(envir);
	update_pwd(envir, 0, old_pwd);
}

void	cd_home(t_vars *vars, char **old_pwd, t_env **envir)
{
	to_home(vars);
	free(*old_pwd);
	*old_pwd = update_old_pwd(envir);
	update_pwd(envir, 0, old_pwd);
}

int	ft_cd(t_vars *vars, t_list *comm, t_env **envir)
{
	static char	*old_pwd;

	vars->exit_status = 0;
	if (comm && comm->next)
	{
		comm = comm->next;
		if (ft_strncmp(comm->content, "-\0", 2) == 0)
			cd_oldpwd(comm, vars, &old_pwd, envir);
		else if (ft_strncmp(comm->content, "~\0", 2) == 0)
			cd_home(vars, &old_pwd, envir);
		else
			regul_dir(vars, &old_pwd, comm, envir);
	}
	else if (comm && !comm->next)
	{
		cd_noargs(envir, vars);
		free(old_pwd);
		old_pwd = update_old_pwd(envir);
		update_pwd(envir, 0, &old_pwd);
	}
	return (0);
}
