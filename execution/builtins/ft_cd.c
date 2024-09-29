/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:34:46 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/29 15:29:39 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	{
		if (*old_pwd)
			free(*old_pwd);
		*old_pwd = update_old_pwd(envir);
		update_pwd(envir, 0, old_pwd);
	}
	free(cwd);
}

void	check_permission(t_vars *vars, t_list *comm)
{
	struct stat	path_stat;

	vars->exit_status = 1;
	if (access(comm->content, F_OK) == -1)
	{
		ft_put_error("minishell: cd:", comm->content,
			": No such file or directory");
		return ;
	}
	if (stat(comm->content, &path_stat) == -1)
	{
		ft_put_error("minishell: cd:", comm->content, ": stat error");
		return ;
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		if (access(comm->content, X_OK) == -1)
			ft_put_error("minishell: cd:", comm->content,
				": Permission denied");
	}
	else
		ft_put_error("minishell: cd:", comm->content, ": Not a directory");
}

void	cd_noargs(t_env **envir, t_vars *vars)
{
	if (chdir(my_getenv("HOME", *envir)))
	{
		vars->exit_status = 1;
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	}
}

void	regul_dir(t_vars *vars, char **old_pwd, t_list *comm, t_env **envir)
{
	if (*comm->content == '\0')
	{
		*old_pwd = update_old_pwd(envir);
		update_pwd(envir, 0, old_pwd);
	}
	if (chdir(comm->content) != -1)
		ft_remove_dir(old_pwd, envir, comm);
	else
		check_permission(vars, comm);
}

int	ft_cd(t_vars *vars, t_list *comm, t_env **envir)
{
	static char	*old_pwd;
	int			first_time;

	first_time = 0;
	if (vars->numofpipes)
		return (0);
	if (comm && comm->next)
	{
		comm = comm->next;
		if (ft_strncmp(comm->content, "-\0", 2) == 0)
		{
			to_oldpwd(comm, &old_pwd, vars, &first_time);
			if (first_time == 0)
			{
				free(old_pwd);
				old_pwd = update_old_pwd(envir);
			}
			update_pwd(envir, 0, &old_pwd);
		}
		else if (ft_strncmp(comm->content, "~\0", 2) == 0)
		{
			to_home(vars);
			free(old_pwd);
			old_pwd = update_old_pwd(envir);
			update_pwd(envir, 0, &old_pwd);
		}
		else
			regul_dir(vars, &old_pwd, comm, envir);
	}
	else if (comm && !comm->next)
	{
		cd_noargs(envir, vars);
		old_pwd = update_old_pwd(envir);
		update_pwd(envir, 0, &old_pwd);
	}
	return (0);
}
