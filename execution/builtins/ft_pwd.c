/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrkik <isrkik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:28:00 by mait-lah          #+#    #+#             */
/*   Updated: 2024/09/04 11:54:08 by isrkik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_vars *vars, t_env *envir, t_list *comm)
{
	char	*pwd;
	t_list *temp;
	
	temp = comm;
	while (comm && comm->type != PIP)
		comm = comm->next;
	if (comm && comm->type == PIP)
	{
		ft_run(vars, temp, envir);
		return (0);
	}
	if (vars->not_red == 0 || (vars->not_enter == 1 && vars->red_built == 1))
	{
		dup2(1, vars->fd_buil);
	}
	else if (vars->red_built == 1 && vars->numofpipes > 0)
	{
		dup2(vars->pfd[1], vars->fd_buil);
	}
	pwd = NULL;
	pwd = getcwd(pwd, PATH_MAX);
	if (!pwd)
		return (perror("getcwd"), errno);
	write(vars->fd_buil, pwd, ft_strlen(pwd));
	ft_putchar_fd('\n', vars->fd_buil);
	return (0);
}

